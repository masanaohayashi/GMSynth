English follows Japanese

# GMSynth

FluidSynthを音源エンジンに使用した、macOS向けのGM系MIDIソフトウェアシンセサイザーです。
JUCEとProjucerで構成され、AUv3とStandalone Pluginを生成します。

## Features

- SoundFont (`.sf2`) のファイル選択と、Security-Scoped bookmarkを利用したState保存・復元
- 16 MIDIチャンネルのミュート、Volume、Pan、Bank、Program操作
- GM準拠のCH10（MIDIチャンネル10、ゼロベースでは9）のドラム固定
- ドラムProgram Changeによるキット切り替え
- 指定Bankにプリセットがない場合のプリセットフォールバック
- GM/GS Reset、All Notes Off、All Sounds Offへの対応
- MIDI入力のタイムスタンプ・サンプルフレーム位置付きCSVログ

SoundFontは同梱していません。利用するSoundFontのライセンスに従ってください。

## Requirements

- macOS
- Xcode
- JUCE 9.0.0（`external/JUCE` のサブモジュール）
- CMake
- Projucer（`.jucer`からXcodeプロジェクトを再生成する場合）

JUCE 9.0.0は `external/JUCE` にサブモジュールとして固定されています。別途、ユーザーのホームディレクトリなどにJUCEを配置する必要はありません。

## Build

サブモジュールを含めて取得します。

```sh
git clone --recurse-submodules https://github.com/masanaohayashi/GMSynth.git
cd GMSynth
```

既にclone済みでサブモジュールだけ未取得の場合は、次を実行します。

```sh
git submodule update --init --recursive
```

FluidSynthの静的ライブラリをビルドします。

```sh
./scripts/build_fluidsynth.sh
```

`cmake`がPATHにない場合は、絶対パスで指定できます。

```sh
CMAKE_BIN=/opt/homebrew/bin/cmake ./scripts/build_fluidsynth.sh
```

その後、`Builds/MacOSX/GMSynth.xcodeproj`をXcodeで開き、`GMSynth - All`をビルドしてください。
Projucerで再生成する場合は、`GMSynth.jucer`を開いてXcode exporterを実行します。

## macOS Release

配布用DMGを作成する前に、初回だけApple Notary Service用のKeychainプロファイルを登録します。秘密鍵やパスワードはリポジトリに保存しないでください。

```sh
xcrun notarytool store-credentials GMSynthNotary \
  --key "/path/to/AuthKey_XXXXXXXXXX.p8" \
  --key-id "XXXXXXXXXX" \
  --issuer "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
```

その後、次のスクリプトを実行すると、Developer ID署名、Universal Releaseビルド、`Applications`リンク入りDMGの作成、Notarization、staple、GitHub Release公開までを行います。

```sh
./scripts/macos/package-release.sh --notary-profile GMSynthNotary
```

署名IDやTeam IDなどを変更する場合は、`scripts/macos/config.env.example`をコピーして `scripts/macos/config.env` を作成してください。

## Runtime

プラグインのUIにある `Load Sound Font` からSoundFontを選択します。
選択したパスとmacOSのSecurity-Scoped bookmarkはプラグインStateに保存され、ホストのプロジェクト保存・復元に使用されます。

AUv3のSandbox環境では、旧StateにSecurity-Scoped bookmarkがない場合、同じSoundFontを一度再選択してからプロジェクトを保存してください。

## Third-party software

- [FluidSynth](https://github.com/FluidSynth/fluidsynth) は `external/fluidsynth` にサブモジュールとして含まれています。ライセンスは同サブモジュールの `LICENSE` を参照してください。
- [JUCE](https://github.com/juce-framework/JUCE) 9.0.0は `external/JUCE` にサブモジュールとして含まれています。JUCEのライセンス条件は同サブモジュールの `LICENSE.md` を参照してください。

## License

GMSynth本体のソースコードはMIT Licenseです。詳細は [LICENSE](LICENSE) を参照してください。

---

# GMSynth

GMSynth is a GM-oriented MIDI software synthesizer for macOS that uses FluidSynth as its sound engine.
It is built with JUCE and Projucer and generates an AUv3 plug-in and a Standalone Plugin.

## Features

- Select SoundFonts (`.sf2`) and save/restore the selection in plug-in state using a Security-Scoped bookmark
- Mute, Volume, Pan, Bank, and Program controls for 16 MIDI channels
- GM-compatible fixed percussion routing for CH10 (MIDI channel 10, zero-based channel 9)
- Drum-kit selection through drum Program Changes
- Preset fallback when the requested bank does not contain the requested program
- GM/GS Reset, All Notes Off, and All Sounds Off handling
- MIDI CSV logging with timestamps and sample-frame positions

SoundFonts are not included. Use each SoundFont in accordance with its license.

## Requirements

- macOS
- Xcode
- JUCE 9.0.0 (included as the `external/JUCE` submodule)
- CMake
- Projucer (only required when regenerating the Xcode project from the `.jucer` file)

JUCE 9.0.0 is pinned as the `external/JUCE` submodule. No separate JUCE installation in the user's home directory is required.

## Build

Clone the repository including its submodules.

```sh
git clone --recurse-submodules https://github.com/masanaohayashi/GMSynth.git
cd GMSynth
```

If the repository was cloned without submodules, initialize them with:

```sh
git submodule update --init --recursive
```

Build the static FluidSynth library:

```sh
./scripts/build_fluidsynth.sh
```

If `cmake` is not on `PATH`, provide its absolute path:

```sh
CMAKE_BIN=/opt/homebrew/bin/cmake ./scripts/build_fluidsynth.sh
```

Then open `Builds/MacOSX/GMSynth.xcodeproj` in Xcode and build the `GMSynth - All` scheme.
To regenerate the project with Projucer, open `GMSynth.jucer` and run the Xcode exporter.

## macOS Release

Before creating a distributable DMG, register a Keychain profile for the Apple Notary Service once. Do not store private keys or passwords in the repository.

```sh
xcrun notarytool store-credentials GMSynthNotary \
  --key "/path/to/AuthKey_XXXXXXXXXX.p8" \
  --key-id "XXXXXXXXXX" \
  --issuer "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
```

Then run the following script. It performs Developer ID signing, a Universal Release build, DMG creation with an `Applications` link, notarization, stapling, and GitHub Release publication.

```sh
./scripts/macos/package-release.sh --notary-profile GMSynthNotary
```

To change the signing identity or Team ID, copy `scripts/macos/config.env.example` to `scripts/macos/config.env` and edit the local file.

## Runtime

Use `Load Sound Font` in the plug-in UI to select a SoundFont.
The selected path and macOS Security-Scoped bookmark are stored in the plug-in state and used when the host saves and restores a project.

In an AUv3 sandbox, if an old state does not contain a Security-Scoped bookmark, select the same SoundFont once again and save the project.

## Third-party software

- [FluidSynth](https://github.com/FluidSynth/fluidsynth) is included as a submodule at `external/fluidsynth`. See the submodule's `LICENSE` for its license.
- [JUCE](https://github.com/juce-framework/JUCE) 9.0.0 is included as the `external/JUCE` submodule. See the submodule's `LICENSE.md` for the JUCE license terms.

## License

The GMSynth source code is released under the MIT License. See [LICENSE](LICENSE) for details.
