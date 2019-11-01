#include <iostream>
#include <cstdlib>
#include <vector>
#include <SFML/Audio.hpp>

using std::vector;

#pragma once
class Audio
{
public:
	Audio(std::string str);

	void PlayAudio();

	void Amplify(float gain);
	void Repeat(int repeats);
	void Normalize();
	void Copy(vector<sf::Int16>& target);
	void Reverse();
	void Combine(vector<sf::Int16> target);
	void Delay(int repeats, float seconds, float attenuation);

	inline vector<sf::Int16>& GetSamples() { return samples; };
protected:

private:
	void die(const char* s);

	sf::SoundBuffer sound_buffer;
	vector<sf::Int16> samples;
};

