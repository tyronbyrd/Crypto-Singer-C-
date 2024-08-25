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
6. A SoundFont file (e.g., 'Rhodes EPs Plus-v2.4.sf2') for use with FluidSynth. You can download the soundfont at https://sites.google.com/site/soundfonts4u/
   just ctl+f 'Rhodes EPs Plus-v2.4.sf2' and download this one and then create a directory and copy past its path into the path variable. You can try other
   soundfonts too, just link the path accordingly. 

   
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
     


ANSWERS FOR 8-2 JOURNAL:

1) Summarize the project and what problem I was solving. 

A: Musical cryptograms are a fun little cryptological trick that famously Bach employed since in German musical notation system, 
   h is b flat in the American system. They are entertaining but laborious to create without making a codex, so I did that. 

2) What did I do particularly well?

A: I think I made something entertaining which is mostly a toy but can actually also be used for more serious musical projects since
   the main impediment to using it as a tool was adjustable beats per minutes, which is a feature I implemented.

2) Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?

A: I wanted to write a mode switcher for the soundfonts which cycles through a revolver of soundfonts so that you can access e.g. a Rhodes electric piano,
   a drum kit, a bass, and a regular piano. The bass and drums sit on different channels so I had to write a MIDI channel switching function which you can
   see is a vestigial element of this work, but I ran into some issues with QT6, namely there is a major bug with implementing the combo box I was trying to 
   use, so I still need to consult the source documentation and see if I can find a method which is simpler, e.g. a button that sends 1-4 and just write an
   if clause. This would make the program more robust and it can almost do that. I just reprogrammed all of this in a day and it got quite late. 

   I would also add more busses. The original version of this program, which I wrote in python and framed first in tkinter then later in pygame; it has 
   multiple busses and it's really easy to basically plop out chiptunes in 5 minutes using FM synthesis through the speakers. That would make this a 
   significantly more serious musical tool.

   Oh yeah, the original of this actually does render .wav's, this one just does playback. This would be a critical feature to add for it to be a musical 
   tool accessibly. Right now anybody who knows how to do a sound loopback or record system audio can use it but I forgot, this one doesn't yet render. 
   Ironically, the difficulty of rendering is higher in C++ than in Python, but playback has been seamless, whereas in Python there were a lot of snags to 
   implementing playback, which required a major rewrite from tkinter into pygame. I'm sure I can find an adequte library, but I started first with playback.

3) Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?

   A: The pieces which were most challenging to write was probably the soundfont functions for fluidsynth. Fluidsynth is really powerful but super touchy and
   needs re-initiated each time so I needed it's own special destructor for cleanup. I can't just leave one instantiation and feed it different paths AFAIK. I
   mostly overcame this by fiddling around imagining namespaces. Wish I could say I had a more technical process but I have been debugging or troubleshooting a
   long time and have a habit of jedi-backflipping into the correct answer through lucky educated guesses and Fluidsynth was one of those such moments. E.g.
   it works great when fluidsynth is initialized first before SMFL; and this sequence was my response to it not working the other way around after first building
   and confirming that fluidsynth worked, then doing SMFL, combining the two; and all the sudden it wasn't working. I don't have an answer to that but setting
   fluidsynth as the default (opposite the original order) worked and solved this issue.

4) What skills from this project will be particularly transferable to other projects or course work?

   A: All of them. Literally all of them, whether using maps to feed information and values or communicating with the system to produce sound or images.
      I think really the only sort of major fundamental in here from a very user oriented perspective is there is not a database for saving the creations
      and the original version actually renders the .wav's while this one just does playback.

5) How did you make this program maintainable, readable, and adaptable?

   A: For the past year I have tried many systems of documentation and have noticed that it is quite possible to over-document inline and make code less
      legible. I'm extremely sight impaired and this is particularly impactful to me. As a result, I think that good code is implicitly legibile to itself
      and serves to self document (self-documenting code). As a result, I tend to name the functions transparently, redundantly label them in case of similar
      names, and write in transparent syntax. I don't really use shorthand code as a result, I do tend to have a more explicit style, and sometimes more verbose,
      but I can at a glance see what everything does and where it sits and I believe that if I can, others can too.

      I made this program more adaptable by writing a MIDI shift function which retrieves the midi values but value shifted from the map. This will allow for
      channel switching to make many types of soundfont possible that use the lower or upper bounds for various reasons, as well as allowing later modulation
      through keys. Further down the road, it would also allow me to implement modes. 

      Implementing a soundfont function also made this program more adaptable than SMFL. SMFL just uses FM synthesis IIRC, and as a result, a person would
      have to do a ton of programming to make various wave shapes, tails, attacks, harmonic compositions; and so on. I did make a nice tail to stop speaker alias,
      hence the note die off-- but the soundfonts allow anybody to download any soundfont, plug it in, and let it rip. They might have to channel switch but
      anything within the same range like piano, trumpets, violins, most woodwinds, chorales, synthesizers; these should just be plug and play after changing
      a path variable. 

   






