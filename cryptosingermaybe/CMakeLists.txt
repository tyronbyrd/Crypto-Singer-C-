cmake_minimum_required(VERSION 3.10)
project(cryptosingermaybe)

set(CMAKE_CXX_STANDARD 17)

# Set the path to find Qt6
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt")

# Find Qt6 and SFML packages
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)

# Specify FluidSynth include and library directories
set(FLUIDSYNTH_ROOT "/opt/homebrew/Cellar/fluid-synth/2.3.6")
set(FLUIDSYNTH_INCLUDE_DIR "${FLUIDSYNTH_ROOT}/include")
set(FLUIDSYNTH_LIBRARY "${FLUIDSYNTH_ROOT}/lib/libfluidsynth.dylib")

# Add the executable
add_executable(cryptosingermaybe main.cpp)

# Link the Qt6 and SFML libraries
target_link_libraries(cryptosingermaybe
        Qt6::Widgets
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        ${FLUIDSYNTH_LIBRARY}
)

# Include directories for FluidSynth
target_include_directories(cryptosingermaybe PRIVATE ${FLUIDSYNTH_INCLUDE_DIR})
