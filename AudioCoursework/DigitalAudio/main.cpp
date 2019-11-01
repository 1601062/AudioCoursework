// CMP407 Digital Audio lab exercise
// Adam Sampson <a.sampson@abertay.ac.uk>
//
// This project was set up based upon: https://www.sfml-dev.org/tutorials/2.5/start-vc.php
// If you need to adjust the paths to the SFML library, see that guide for more information.
// SFML is assumed to be in M:\sfml, and the project is being built in Debug x64 mode.

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//
#include "Game.h"
#include "Audio.h"

//
using std::cerr;
using std::vector;

void die(const char *s) {
	cerr << "Fatal: " << s << "\n";
	cerr << "Current directory is:\n";
	system("cd");
	system("pause");
	exit(1);
}

int main() {
	//
	sf::RenderWindow window(sf::VideoMode(650, 650), "Soundwave");
	//
	Game game(&window);
	//
	sf::Clock time;
	//
	Audio cowbell("quiet_Cowbell.wav");;
	Audio cymbal("cra_Rock_a.wav");
	Audio backwards_cymbal("cra_Rock_a.wav");
	// Cowbell effects
	cowbell.Normalize();
	cowbell.Reverse();
	cowbell.Delay(5, 100, 0.9);
	// Cymbal effects
	cymbal.Normalize();
	cymbal.Delay(5, 0.3, 0.5);
	// Backwards cymbal effects
	backwards_cymbal.Normalize();
	backwards_cymbal.Reverse();
	backwards_cymbal.Combine(cymbal.GetSamples());
	backwards_cymbal.Normalize();

	// run the program as long as the window is open
	while (window.isOpen())
	{
		game.update(time.getElapsedTime().asMilliseconds());
		game.render();

		cymbal.PlayAudio();
		//backwards_cymbal.PlayAudio();
		//cymbal.PlayAudio();

		
	

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	return 0;
}