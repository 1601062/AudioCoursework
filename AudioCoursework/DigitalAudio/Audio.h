#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <SFML/Audio.hpp>

using std::vector;

class Audio
{
public:
	Audio();
	Audio(std::string str);

	void Play();
	void Reset();

	void Normalize();
	void RemoveBackground(int cutoff);

	void Amplify(float gain);
	void DistanceAttenuation(float distance, float maxDistance);
	void Repeat(int repeats);
	void Copy(vector<sf::Int16>& target);
	void Reverse();
	void Combine(vector<sf::Int16> target);
	void Delay(int repeats, float seconds, float attenuation);

	inline vector<sf::Int16>& GetSamples() { return samples; };
protected:

private:
	void die(const char* s);

	vector<sf::Int16> samples;			// Holds sound samples. 
	vector<sf::Int16> samplesBackup;	// For resetting samples back to original unaltered sound effect.
	sf::SoundBuffer modBuffer;			// Required for loading of wav file.
	sf::Sound sound;					// The sound object used by SFML to play audio.

};

