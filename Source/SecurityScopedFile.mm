#include "SecurityScopedFile.h"

#if JUCE_MAC

#import <Foundation/Foundation.h>

namespace
{
NSURL* fileURL (const juce::File& file)
{
    const auto path = file.getFullPathName();
    return [NSURL fileURLWithPath: [NSString stringWithUTF8String: path.toRawUTF8()]];
}

juce::String juceString (NSString* string)
{
    return juce::String::fromUTF8 ([string UTF8String]);
}

juce::String makeBookmark (NSURL* url)
{
    if (url == nil)
        return {};

    NSError* error = nil;
    NSData* data = [url bookmarkDataWithOptions: NSURLBookmarkCreationWithSecurityScope
                  includingResourceValuesForKeys: nil
                                           relativeToURL: nil
                                                 error: &error];

    if (data == nil || error != nil)
        return {};

    juce::MemoryBlock bytes (data.bytes, data.length);
    return bytes.toBase64Encoding();
}
}

namespace GMSynthSecurity
{
struct ScopedSoundFontFileAccess::Impl
{
    __strong NSURL* url = nil;
    bool accessStarted = false;
    bool usable = false;
};

juce::String createSecurityScopedBookmark (const juce::File& file)
{
    @autoreleasepool
    {
        return makeBookmark (fileURL (file));
    }
}

ScopedSoundFontFileAccess::ScopedSoundFontFileAccess (const juce::File& fileToUse,
                                                       const juce::String& bookmarkData)
    : impl (std::make_unique<Impl>()),
      file (fileToUse),
      refreshedBookmark (bookmarkData)
{
    @autoreleasepool
    {
        if (bookmarkData.isNotEmpty())
        {
            juce::MemoryBlock bookmarkBytes;
            if (! bookmarkBytes.fromBase64Encoding (bookmarkData))
            {
                impl->usable = file.existsAsFile();
                return;
            }

            NSData* data = [NSData dataWithBytes: bookmarkBytes.getData()
                                           length: bookmarkBytes.getSize()];
            BOOL isStale = NO;
            NSError* error = nil;
            NSURL* resolvedURL = [NSURL URLByResolvingBookmarkData: data
                                                            options: NSURLBookmarkResolutionWithSecurityScope
                                                      relativeToURL: nil
                                                bookmarkDataIsStale: &isStale
                                                              error: &error];

            auto usedLegacyBookmark = false;
            if (resolvedURL == nil || error != nil)
            {
                // Bookmarks written by an older/unsandboxed build may not
                // contain a security scope. Try the regular bookmark form so
                // it can still work when the current process has access.
                error = nil;
                isStale = NO;
                resolvedURL = [NSURL URLByResolvingBookmarkData: data
                                                          options: 0
                                                    relativeToURL: nil
                                              bookmarkDataIsStale: &isStale
                                                            error: &error];
                usedLegacyBookmark = true;
            }

            if (resolvedURL == nil || error != nil)
            {
                impl->usable = file.existsAsFile();
                return;
            }

            const auto accessStarted = [resolvedURL startAccessingSecurityScopedResource];

           #if __has_feature (objc_arc)
            impl->url = resolvedURL;
           #else
            impl->url = [resolvedURL retain];
           #endif
            impl->accessStarted = accessStarted;
            file = juce::File (juceString (resolvedURL.path));
            impl->usable = file.existsAsFile();

            if (isStale || usedLegacyBookmark)
            {
                const auto refreshed = makeBookmark (resolvedURL);
                if (refreshed.isNotEmpty())
                    refreshedBookmark = refreshed;
            }

            return;
        }

        impl->usable = file.existsAsFile();
    }
}

ScopedSoundFontFileAccess::~ScopedSoundFontFileAccess()
{
    if (impl == nullptr)
        return;

    @autoreleasepool
    {
        if (impl->accessStarted && impl->url != nil)
            [impl->url stopAccessingSecurityScopedResource];

       #if ! __has_feature (objc_arc)
        [impl->url release];
       #endif
    }
}

bool ScopedSoundFontFileAccess::isUsable() const noexcept
{
    return impl != nullptr && impl->usable;
}

const juce::File& ScopedSoundFontFileAccess::getFile() const noexcept
{
    return file;
}

const juce::String& ScopedSoundFontFileAccess::getRefreshedBookmark() const noexcept
{
    return refreshedBookmark;
}
}

#else

namespace GMSynthSecurity
{
struct ScopedSoundFontFileAccess::Impl
{
    bool usable = false;
};

juce::String createSecurityScopedBookmark (const juce::File&)
{
    return {};
}

ScopedSoundFontFileAccess::ScopedSoundFontFileAccess (const juce::File& fileToUse,
                                                       const juce::String&)
    : impl (std::make_unique<Impl>()),
      file (fileToUse)
{
    impl->usable = file.existsAsFile();
}

ScopedSoundFontFileAccess::~ScopedSoundFontFileAccess() = default;

bool ScopedSoundFontFileAccess::isUsable() const noexcept
{
    return impl != nullptr && impl->usable;
}

const juce::File& ScopedSoundFontFileAccess::getFile() const noexcept
{
    return file;
}

const juce::String& ScopedSoundFontFileAccess::getRefreshedBookmark() const noexcept
{
    static const juce::String empty;
    return empty;
}
}

#endif
