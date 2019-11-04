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
#include "Input.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1300, 650), "Audio Game!");
	Input input;
	window.setFramerateLimit(60.0f);
	Game game(&window, &input);
	sf::Clock time;

	// RUN THE PROGRAM AS LONG AS THE WINDOW IS OPEN
	while (window.isOpen())
	{
		game.update(time.getElapsedTime().asMilliseconds());
		game.render();
		
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				break;
			case sf::Event::KeyPressed:
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				input.setKeyUp(event.key.code);
				break;
			default:
				// don't handle other events
				break;
			}
		}
	}

	return 0;
}