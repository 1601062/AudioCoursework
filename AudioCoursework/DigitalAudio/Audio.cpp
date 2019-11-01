#include "Audio.h"

using std::cerr;
using std::vector;

void Audio::die(const char* s) {
	cerr << "Fatal: " << s << "\n";
	cerr << "Current directory is:\n";
	system("cd");
	system("pause");
	exit(1);
}

Audio::Audio(std::string str)
{
	// sf::SoundBuffer holds a sampled sound, using signed 16-bit samples.
	// We can load one from a file...
	if (!sound_buffer.loadFromFile(str)) {
		die("loading failed");
	}

	// We can read out the samples -- let's copy them into a vector
	const sf::Int16* data = sound_buffer.getSamples();
	vector<sf::Int16> soundsamples(data, data + sound_buffer.getSampleCount());
	samples = soundsamples;
}

void Audio::PlayAudio() {
	// Create a new buffer from the vector.
	sf::SoundBuffer modBuffer;
	modBuffer.loadFromSamples(samples.data(), samples.size(), 1, 44100);

	// sf::Sound controls playback of a sound.
	sf::Sound sound(modBuffer);

	// play() starts playback in a separate thread -- so it returns
	// immediately, with the sound playing in the background.
	sound.play();

	// wait for the sound to finish playing
	while (sound.getStatus() == sf::Sound::Playing) {
		sf::sleep(sf::milliseconds(1));
	}
}

void Audio::Amplify(float gain) {
	for (int i = 0; i < samples.size(); i++) {
		samples.at(i) *= gain;
	}
}

void Audio::Repeat(int repeats) {
	samples.insert(samples.end(), samples.begin(), samples.end());
}

void Audio::Normalize() {
	// HIGHEST AND LOWEST
	sf::Int16 highest = 00000000;
	sf::Int16 lowest = 99999999;

	for (int i = 0; i < samples.size(); i++) {
		if (samples.at(i) > highest) {
			highest = samples.at(i);
		}
		if (samples.at(i) < lowest) {
			lowest = samples.at(i);
		}
	}

	std::cout << highest << std::endl << lowest << std::endl;

	float multiplier;
	if (highest > -lowest) {
		multiplier = 32767 / highest;
	}
	else if (highest <= -lowest) {
		multiplier = 32768 / -lowest;
	}

	for (int i = 0; i < samples.size(); i++) {
		samples.at(i) *= multiplier;
	}
}

void Audio::Copy(vector<sf::Int16>& target) {
	target = samples;
}

void Audio::Reverse() {
	std::reverse(samples.begin(), samples.end());
}

void Audio::Combine(vector<sf::Int16> target) {
	for (int i = 0; i < target.size(); i++)
	{
		samples.at(i) += target.at(i);
	}
}

void Audio::Delay(int repeats, float seconds, float attenuation) {
	// Convert seconds to Hz
	int ms_delay = seconds * 44100;
	// Create vector of vectors (vector of echo samples)
	vector<vector<sf::Int16>> echoes;
	// Fill initial echo with samples as is
	echoes.push_back(samples);
	for (int i = 0; i < repeats; i++) {
		std::vector<sf::Int16> silence(ms_delay);
		// insert silence
		echoes.at(i).insert(echoes.at(i).begin(), silence.begin(), silence.end());
		// attenuation
		for (int j = 0; j < samples.size(); j++) {
			echoes.at(i).at(j) *= attenuation;
		}
		// Next echo
		echoes.push_back(echoes.at(i));
	}
	// Combine echoes with samples
	for (int i = 0; i < repeats; i++) {
		for (int j = 0; j < samples.size(); j++) {
			samples.at(j) += echoes.at(i).at(j);
		}
	}
}