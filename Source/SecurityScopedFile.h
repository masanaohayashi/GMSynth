#pragma once

#include <JuceHeader.h>

#include <memory>

namespace GMSynthSecurity
{
juce::String createSecurityScopedBookmark (const juce::File& file);

class ScopedSoundFontFileAccess
{
public:
    ScopedSoundFontFileAccess (const juce::File& file, const juce::String& bookmarkData);
    ~ScopedSoundFontFileAccess();

    bool isUsable() const noexcept;
    const juce::File& getFile() const noexcept;
    const juce::String& getRefreshedBookmark() const noexcept;

private:
    struct Impl;

    std::unique_ptr<Impl> impl;
    juce::File file;
    juce::String refreshedBookmark;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScopedSoundFontFileAccess)
};
}
