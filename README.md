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
- JUCE 8.0.13（または互換性のあるJUCE 8系）
- CMake
- Projucer（`.jucer`からXcodeプロジェクトを再生成する場合）

`GMSynth.jucer`とチェックイン済みのXcodeプロジェクトは、JUCEがユーザーのホームディレクトリ直下にある構成を前提にしています。
別の場所にJUCEを置く場合は、ProjucerでJUCEのModule Pathを設定し直してから再エクスポートしてください。

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

## Runtime

プラグインのUIにある `Load Sound Font` からSoundFontを選択します。
選択したパスとmacOSのSecurity-Scoped bookmarkはプラグインStateに保存され、ホストのプロジェクト保存・復元に使用されます。

AUv3のSandbox環境では、旧StateにSecurity-Scoped bookmarkがない場合、同じSoundFontを一度再選択してからプロジェクトを保存してください。

## Third-party software

- [FluidSynth](https://github.com/FluidSynth/fluidsynth) は `external/fluidsynth` にサブモジュールとして含まれています。ライセンスは同サブモジュールの `LICENSE` を参照してください。
- JUCEはリポジトリに同梱していません。JUCEのライセンス条件に従ってください。

## License

GMSynth本体のソースコードはMIT Licenseです。詳細は [LICENSE](LICENSE) を参照してください。
