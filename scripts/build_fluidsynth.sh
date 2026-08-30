#!/bin/sh

set -eu

fluid_script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
fluid_project_root=$(CDPATH= cd -- "$fluid_script_dir/.." && pwd)
fluid_source_dir="$fluid_project_root/external/fluidsynth"
fluid_build_dir="$fluid_source_dir/build"

fluid_cmake="${CMAKE_BIN:-}"
if [ -z "$fluid_cmake" ]; then
    fluid_cmake=$(command -v cmake 2>/dev/null || true)
fi

if [ -z "$fluid_cmake" ]; then
    for candidate in \
        /opt/homebrew/bin/cmake \
        /usr/local/bin/cmake \
        /opt/local/bin/cmake \
        /Applications/CMake.app/Contents/bin/cmake
    do
        if [ -x "$candidate" ]; then
            fluid_cmake="$candidate"
            break
        fi
    done
fi

if [ -z "$fluid_cmake" ] || [ ! -x "$fluid_cmake" ]; then
    echo "CMake was not found. Install CMake or set CMAKE_BIN to its absolute path." >&2
    exit 127
fi

case "${CONFIGURATION:-Release}" in
    Debug)
        fluid_build_type=Debug
        ;;
    Release)
        fluid_build_type=Release
        ;;
    *)
        fluid_build_type=RelWithDebInfo
        ;;
esac

if [ -n "${ARCHS:-}" ]; then
    fluid_architectures=$(printf '%s' "$ARCHS" | tr ' ' ';')
else
    fluid_architectures=$(uname -m)
fi

"$fluid_cmake" -S "$fluid_source_dir" -B "$fluid_build_dir" \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_BUILD_TYPE="$fluid_build_type" \
    -DCMAKE_OSX_ARCHITECTURES="$fluid_architectures" \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -Denable-framework=OFF \
    -Denable-coreaudio=OFF \
    -Denable-coremidi=OFF \
    -Denable-aufile=OFF \
    -Denable-alsa=OFF \
    -Denable-dbus=OFF \
    -Denable-jack=OFF \
    -Denable-ladspa=OFF \
    -Denable-libsndfile=OFF \
    -Denable-midishare=OFF \
    -Denable-network=OFF \
    -Denable-oss=OFF \
    -Denable-pipewire=OFF \
    -Denable-portaudio=OFF \
    -Denable-pulseaudio=OFF \
    -Denable-readline=OFF \
    -Denable-sdl3=OFF \
    -Denable-signalsmith=OFF \
    -Denable-openmp=OFF \
    -Denable-native-dls=OFF \
    -Denable-threads=ON

"$fluid_cmake" --build "$fluid_build_dir" --target libfluidsynth -- -j2
