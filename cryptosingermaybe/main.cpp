#include <fluidsynth.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QDesktopServices>
#include <QUrl>
#include <QThread>
#include <chrono>
#include <thread>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>


class MusicalCryptogramGenerator : public QWidget {
public:
    MusicalCryptogramGenerator(QWidget* parent = nullptr) : QWidget(parent), useSynthesizer(true), sfid(-1) {
        // Initialize the GUI
        this->setWindowTitle("Musical Cryptogram Generator C++ v.0.1");
        this->setFixedSize(390, 400);
        this->setStyleSheet("background-color: #229b75;");

        // Layouts
        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        QHBoxLayout* inputLayout = new QHBoxLayout();
        QHBoxLayout* bpmLayout = new QHBoxLayout();

        // Widgets
        QLabel* inputLabel = new QLabel("Enter your input string:", this);
        inputEntry = new QLineEdit(this);

        QLabel* bpmLabel = new QLabel("Set BPM:", this);
        bpmEntry = new QLineEdit(this);
        bpmEntry->setText("60");  // Default BPM value

        translateButton = new QPushButton("Translate!", this);
        playbackButton = new QPushButton("Playback!", this);
        switchModeButton = new QPushButton("Switch to Synthesizer", this);

        resultText = new QTextEdit(this);
        resultText->setFixedHeight(150);
        resultText->setReadOnly(true);

        QIcon icon("/Users/tyron/CLionProjects/cryptosingermaybe/icon.png");
        QPushButton* iconButton = new QPushButton(this);
        iconButton->setIcon(icon);
        iconButton->setIconSize(QSize(24, 24));

        // Set Styles
        translateButton->setStyleSheet("background-color: #4bae75; color: black; font: bold 12px Arial;");
        playbackButton->setStyleSheet("background-color: #4bae75; color: black; font: bold 12px Arial;");
        switchModeButton->setStyleSheet("background-color: #4bae75; color: black; font: bold 12px Arial;");

        // Add widgets to layouts
        inputLayout->addWidget(inputLabel);
        inputLayout->addWidget(inputEntry);

        bpmLayout->addWidget(bpmLabel);
        bpmLayout->addWidget(bpmEntry);

        mainLayout->addLayout(inputLayout);
        mainLayout->addLayout(bpmLayout);
        mainLayout->addWidget(translateButton);
        mainLayout->addWidget(playbackButton);
        mainLayout->addWidget(switchModeButton);
        mainLayout->addWidget(resultText);
        mainLayout->addWidget(iconButton, 0, Qt::AlignCenter);

        // Connect signals and slots
        connect(translateButton, &QPushButton::clicked, this, &MusicalCryptogramGenerator::translateAndRender);
        connect(playbackButton, &QPushButton::clicked, this, &MusicalCryptogramGenerator::playSoundFromNotes);
        connect(switchModeButton, &QPushButton::clicked, this, &MusicalCryptogramGenerator::switchMode);
        connect(iconButton, &QPushButton::clicked, this, &MusicalCryptogramGenerator::openWebpage);

        // Initialize FluidSynth
        settings = new_fluid_settings();
        synth = new_fluid_synth(settings);
        adriver = new_fluid_audio_driver(settings, synth); // Provide synth as the first argument
        loadSoundFont("/Users/tyron/soundfonts/Rhodes EPs Plus-v2.4.sf2");
    }

    ~MusicalCryptogramGenerator() {
        cleanupFluidSynth();
    }

private:
    QLineEdit* inputEntry;
    QLineEdit* bpmEntry;
    QTextEdit* resultText;
    QPushButton* translateButton;
    QPushButton* playbackButton;
    QPushButton* switchModeButton;
    std::vector<std::string> playbackNotes;
    bool useSynthesizer;  // To toggle between Synthesizer and SoundFont

    fluid_settings_t* settings;
    fluid_synth_t* synth;
    fluid_audio_driver_t* adriver;
    int sfid;

    std::map<std::string, double> NOTE_FREQS = {
        {"C3", 130.81}, {"C#3/Db3", 138.59}, {"D3", 146.83}, {"D#3/Eb3", 155.56}, {"E3", 164.81},
        {"F3", 174.61}, {"F#3/Gb3", 185.00}, {"G3", 196.00}, {"G#3/Ab3", 207.65}, {"A3", 220.00},
        {"A#3/Bb3", 233.08}, {"B3", 246.94}, {"C4", 261.63}, {"C#4/Db4", 277.18}, {"D4", 293.66},
        {"D#4/Eb4", 311.13}, {"E4", 329.63}, {"F4", 349.23}, {"F#4/Gb4", 369.99}, {"G4", 392.00},
        {"G#4/Ab4", 415.30}, {"A4", 440.00}, {"A#4/Bb4", 466.16}, {"B4", 493.88}, {"C5", 523.25},
        {"C#5/Db5", 554.37}, {"D5", 587.33}, {"D#5/Eb5", 622.25}, {"E5", 659.25}, {"F5", 698.46},
        {"F#5/Gb5", 739.99}, {"G5", 783.99}, {"G#5/Ab5", 830.61}, {"A5", 880.00}, {"A#5/Bb5", 932.33},
        {"B5", 987.77}, {"C6", 1046.50}, {"C#6/Db6", 1108.73}, {"D6", 1174.66}, {"D#6/Eb6", 1244.51},
        {"E6", 1318.51}, {"F6", 1396.91}, {"F#6/Gb6", 1479.98}, {"G6", 1567.98}, {"G#6/Ab6", 1661.22},
        {"A6", 1760.00}, {"A#6/Bb6", 1864.66}, {"B6", 1975.53}, {"C7", 2093.00}, {"C#7/Db7", 2217.46},
        {"D7", 2349.32}, {"D#7/Eb7", 2489.02}, {"E7", 2637.02}, {"F7", 2793.83}, {"F#7/Gb7", 2959.96},
        {"G7", 3135.96}, {"G#7/Ab7", 3322.44}, {"A7", 3520.00}, {"A#7/Bb7", 3729.31}, {"B7", 3951.07}
    };

    void loadSoundFont(const std::string& soundFontPath) {
        sfid = fluid_synth_sfload(synth, soundFontPath.c_str(), 1);
        if (sfid == -1) {
            std::cerr << "Failed to load SoundFont!" << std::endl;
        } else {
            std::cout << "SoundFont loaded successfully!" << std::endl;
            fluid_synth_set_bank_offset(synth, sfid, 0); // Reset bank offset with the correct SoundFont ID
            int program = 0; // Program number for the instrument
            fluid_synth_program_select(synth, 0, sfid, 0, program);
        }
    }

    void cleanupFluidSynth() {
        if (adriver) delete_fluid_audio_driver(adriver);
        if (synth) delete_fluid_synth(synth);
        if (settings) delete_fluid_settings(settings);
    }

    void translateAndRender() {
        std::string inputText = inputEntry->text().toStdString();
        std::vector<std::string> notes;

        for (char& c : inputText) {
            std::string note = charToNoteMapping(c);
            if (!note.empty()) notes.push_back(note);
        }

        playbackNotes = notes;

        std::string result = "";
        for (const std::string& note : notes) {
            result += note + " ";
        }

        resultText->setText(QString::fromStdString(result));
    }

    std::string charToNoteMapping(char c) {
        static const std::map<char, std::string> mapping = {
            {'A', "C4"}, {'B', "D4"}, {'C', "E4"}, {'D', "F4"},
            {'E', "G4"}, {'F', "A4"}, {'G', "B4"}, {'H', "C5"},
            {'I', "D5"}, {'J', "E5"}, {'K', "F5"}, {'L', "G5"},
            {'M', "A5"}, {'N', "B5"}, {'O', "C6"}, {'P', "D6"},
            {'Q', "E6"}, {'R', "F6"}, {'S', "G6"}, {'T', "A6"},
            {'U', "B6"}, {'V', "C7"}, {'W', "D7"}, {'X', "E7"},
            {'Y', "F7"}, {'Z', "G7"}, {' ', " "}
        };

        char upperC = toupper(c);
        auto it = mapping.find(upperC);
        return it != mapping.end() ? it->second : "";
    }

    void playSoundFromNotes() {
        if (useSynthesizer) {
            playUsingSoundFont();
        } else {
            playUsingSFML();
        }
    }

    void playUsingSFML() {
        double bpm = bpmEntry->text().toDouble();
        double beatDuration = 60.0 / bpm;

        for (const std::string& note : playbackNotes) {
            if (note == "REST") {
                sf::sleep(sf::seconds(beatDuration));
            } else {
                double freq = NOTE_FREQS[note];
                sf::SoundBuffer buffer = generateSineWave(freq, beatDuration);
                sf::Sound sound;
                sound.setBuffer(buffer);
                sound.play();
                sf::sleep(sf::seconds(beatDuration));
            }
        }
    }

    void playUsingSoundFont() {
        double bpm = bpmEntry->text().toDouble();
        double beatDuration = 60.0 / bpm * 1000; // Convert to milliseconds

        std::cout << "Playing notes with SoundFont:" << std::endl;
        for (const std::string& note : playbackNotes) {
            std::cout << "Note: " << note << std::endl;
            if (note != "REST") {
                //FIXME!!! getShiftedMidiKey(note, shift) to channel hop, else noteToMidiKey(note)
                int key = getShiftedMidiKey(note, +30);
                std::cout << "MIDI Key: " << key << std::endl;
                fluid_synth_noteon(synth, 0, key, 80);  // Channel 0, Velocity 80
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(beatDuration)));
                fluid_synth_noteoff(synth, 0, key);
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(beatDuration))); // REST
            }
        }
    }

    sf::SoundBuffer generateSineWave(double frequency, double duration) {
        const int sampleRate = 44100;
        const int sampleCount = static_cast<int>(sampleRate * duration);
        std::vector<sf::Int16> samples(sampleCount);

        // Create sine wave with fade-out
        for (int i = 0; i < sampleCount; ++i) {
            double t = i / static_cast<double>(sampleRate);
            double fadeOutFactor = 1.0 - std::min(1.0, t / duration); // Linear fade-out
            samples[i] = static_cast<sf::Int16>(32767 * 0.5 * fadeOutFactor * sin(2 * M_PI * frequency * i / sampleRate));
        }

        sf::SoundBuffer buffer;
        if (!buffer.loadFromSamples(samples.data(), samples.size(), 1, sampleRate)) {
            std::cerr << "Failed to load sound buffer!" << std::endl;
        }
        return buffer;
    }


    int noteToMidiKey(const std::string& note) {
        static const std::map<std::string, int> midiMapping = {
            {"C3", 48}, {"C#3/Db3", 49}, {"D3", 50}, {"D#3/Eb3", 51}, {"E3", 52},
            {"F3", 53}, {"F#3/Gb3", 54}, {"G3", 55}, {"G#3/Ab3", 56}, {"A3", 57},
            {"A#3/Bb3", 58}, {"B3", 59}, {"C4", 60}, {"C#4/Db4", 61}, {"D4", 62},
            {"D#4/Eb4", 63}, {"E4", 64}, {"F4", 65}, {"F#4/Gb4", 66}, {"G4", 67},
            {"G#4/Ab4", 68}, {"A4", 69}, {"A#4/Bb4", 70}, {"B4", 71}, {"C5", 72},
            {"C#5/Db5", 73}, {"D5", 74}, {"D#5/Eb5", 75}, {"E5", 76}, {"F5", 77},
            {"F#5/Gb5", 78}, {"G5", 79}, {"G#5/Ab5", 80}, {"A5", 81}, {"A#5/Bb5", 82},
            {"B5", 83}, {"C6", 84}, {"C#6/Db6", 85}, {"D6", 86}, {"D#6/Eb6", 87},
            {"E6", 88}, {"F6", 89}, {"F#6/Gb6", 90}, {"G6", 91}, {"G#6/Ab6", 92},
            {"A6", 93}, {"A#6/Bb6", 94}, {"B6", 95}, {"C7", 96}, {"C#7/Db7", 97},
            {"D7", 98}, {"D#7/Eb7", 99}, {"E7", 100}, {"F7", 101}, {"F#7/Gb7", 102},
            {"G7", 103}, {"G#7/Ab7", 104}, {"A7", 105}, {"A#7/Bb7", 106}, {"B7", 107}
        };
        auto it = midiMapping.find(note);
        return it != midiMapping.end() ? it->second : 0; // Return 0 for unknown notes
    }

    // Function to get the MIDI key with an optional shift
    int getShiftedMidiKey(const std::string& note, int shift) {
        static const std::map<std::string, int> midiMapping = {
            {"C3", 48}, {"C#3/Db3", 49}, {"D3", 50}, {"D#3/Eb3", 51}, {"E3", 52},
            {"F3", 53}, {"F#3/Gb3", 54}, {"G3", 55}, {"G#3/Ab3", 56}, {"A3", 57},
            {"A#3/Bb3", 58}, {"B3", 59}, {"C4", 60}, {"C#4/Db4", 61}, {"D4", 62},
            {"D#4/Eb4", 63}, {"E4", 64}, {"F4", 65}, {"F#4/Gb4", 66}, {"G4", 67},
            {"G#4/Ab4", 68}, {"A4", 69}, {"A#4/Bb4", 70}, {"B4", 71}, {"C5", 72},
            {"C#5/Db5", 73}, {"D5", 74}, {"D#5/Eb5", 75}, {"E5", 76}, {"F5", 77},
            {"F#5/Gb5", 78}, {"G5", 79}, {"G#5/Ab5", 80}, {"A5", 81}, {"A#5/Bb5", 82},
            {"B5", 83}, {"C6", 84}, {"C#6/Db6", 85}, {"D6", 86}, {"D#6/Eb6", 87},
            {"E6", 88}, {"F6", 89}, {"F#6/Gb6", 90}, {"G6", 91}, {"G#6/Ab6", 92},
            {"A6", 93}, {"A#6/Bb6", 94}, {"B6", 95}, {"C7", 96}, {"C#7/Db7", 97},
            {"D7", 98}, {"D#7/Eb7", 99}, {"E7", 100}, {"F7", 101}, {"F#7/Gb7", 102},
            {"G7", 103}, {"G#7/Ab7", 104}, {"A7", 105}, {"A#7/Bb7", 106}, {"B7", 107}
        };

        auto it = midiMapping.find(note);
        if (it != midiMapping.end()) {
            return it->second - shift; // Apply shift
        } else {
            return -1; // Return -1 or some other value for unknown notes
        }
    }
    // FIXME use that traffic light thingy instead of bool to switch? keep usesynth to
    // trigger the case?
    void switchMode() {
        useSynthesizer = !useSynthesizer;
        QString buttonText = useSynthesizer ? "Switch to Synthesizer" : "Switch to Soundfont";
        switchModeButton->setText(buttonText);
    }

    void openWebpage() {
        QDesktopServices::openUrl(QUrl("https://tyronbyrd.com")); // Change URL as needed
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MusicalCryptogramGenerator window;
    window.show();
    return app.exec();
}
