Musical Cryptogram Generator C++ Project

Introduction

This project is a C++ application called 'Musical Cryptogram Generator' that translates input text into musical notes and plays them back. 
The application uses a combination of Qt for the graphical user interface, FluidSynth for SoundFont playback, and SFML for audio playback. 
The application allows switching between SoundFont synthesizer playback and sine wave playback using SFML.


Prerequisites

Before assembling and running this project, ensure the following software is installed on your machine:
NOTE: INSTRUCTIONS APPENDED AT BOTTOM OF README

1. Qt 5 or higher
2. CMake 3.5 or higher
3. A C++ compiler that supports C++11 standard or higher (e.g., GCC, Clang, MSVC)
4. FluidSynth library
5. SFML library
6. A SoundFont file (e.g., 'Rhodes EPs Plus-v2.4.sf2') for use with FluidSynth

   
Installation

1. Clone the Repository
   
Clone the repository to your local machine using the following command:
```
git clone https://github.com/tyronbyrd/musical-cryptogram-generator.git
```

2. Install Dependencies
   
Ensure you have all required dependencies installed. This includes Qt, CMake, a C++ compiler, FluidSynth, and SFML. 
You may need to install these via your system's package manager or from their respective websites.

4. Setup FluidSynth and SFML
   
Download and install FluidSynth and SFML. Ensure that both libraries are properly set up on your system and that you 
have the necessary development headers and libraries. You may need to set the library paths in your IDE or build system.

6. Set Up the SoundFont
   
Download a SoundFont file (e.g., 'Rhodes EPs Plus-v2.4.sf2') and place it in an appropriate directory. 
Update the path to this SoundFont in the source code (e.g., in the `loadSoundFont()` method of `MusicalCryptogramGenerator`).


Building the Project

1. Using CMake
   
Create a build directory and run CMake to generate the makefiles:
```
mkdir build
cd build
cmake ..
make
```

2. Using Qt Creator
   
Open the `.pro` file in Qt Creator. Configure the project using the IDE to include the necessary libraries (FluidSynth, SFML). 
Build the project using the IDE's build tools.


Running the Application

After building the project, run the executable from the command line or your IDE. The application window will appear, 
allowing you to enter a string, set the BPM, translate the input into notes, and play it back.

Usage

1. **Enter your input string:** Type the text you want to convert to music.
2. **Set BPM:** Adjust the BPM (Beats Per Minute) for playback.
3. **Translate!** Click the 'Translate!' button to convert the text into musical notes.
4. **Playback!** Click the 'Playback!' button to play the generated notes using the selected mode (Synthesizer or SFML).
5. **Switch Mode:** Click the 'Switch to Synthesizer' button to toggle between SoundFont synthesizer playback and SFML sine wave playback.
   
Notes

Ensure that the SoundFont path is correctly set in the source code and that FluidSynth can access the SoundFont file.

This project is designed to run on systems with a properly configured audio setup. Make sure your system's audio output is functioning correctly.

License

You may use this free of charge and alter the source code, but please credit me if you use it for commercial or artistic purposes. 



DEPENDENCY INSTALLATION INSTRUCTIONS

How to Install Dependencies for the Musical Cryptogram Generator C++ Project

This guide provides step-by-step instructions for installing the required dependencies to compile and run the Musical Cryptogram Generator C++ project.

1. Installing Qt
   
Qt is a free and open-source widget toolkit for creating graphical user interfaces. To install Qt:

  1. Visit the official Qt website: https://www.qt.io/download.
  2. Download the Qt Online Installer for your operating system or or using brew install `brew install --cask qt-creator`
  3. Run the installer and follow the on-screen instructions.
  4. During the installation process, ensure that you select the components for Qt 5.x or 6.x (depending on your project requirement) and the Qt Creator IDE.
  5. After installation, set the environment variables if necessary, and verify the installation by opening Qt Creator.

2. Installing SFML
   
SFML (Simple and Fast Multimedia Library) is used for audio and graphics handling. To install SFML:

  1. Visit the official SFML website: https://www.sfml-dev.org/download.php.
  2. Download the appropriate version for your operating system (Windows, macOS, or Linux).
  3. Extract the downloaded archive to a directory of your choice.
  4. For Windows, set the environment variable for SFML to the extracted directory.
  5. For Linux/macOS, install SFML using your package manager, e.g., `sudo apt-get install libsfml-dev` on Debian-based systems,
     or using brew install `brew install sfml`.

3. Installing FluidSynth
   
FluidSynth is a real-time software synthesizer. To install FluidSynth:

  1. Visit the official FluidSynth GitHub repository: https://github.com/FluidSynth/fluidsynth.
  2. Follow the instructions to clone the repository and build from source if binaries are not available for your platform.
  3. Alternatively, use a package manager to install, e.g., `sudo apt-get install fluidsynth` for Debian-based Linux or `brew install fluidsynth` for macOS.
  4. Verify the installation by running `fluidsynth --version` in the terminal.
  4. Installing Additional Libraries
     




