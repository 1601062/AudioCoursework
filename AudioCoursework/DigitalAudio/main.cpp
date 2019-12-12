// CMP407 Digital Audio Coursework Project
// Alien Santa and the Zombie Elf UFO Apocalypse Chimney Bonanza

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

using std::cerr;

void die(bool win) {
	if (win) {
		cerr << "Congratulations. \n";
		cerr << "You've saved alien Christmas. \n";
		system("cd");
		system("pause");
		exit(1);
	}
	else {
		cerr << "Congratulations. \n";
		cerr << "You've ruined alien Christmas. \n";
		system("cd");
		system("pause");
		exit(1);
	}
}


int main() {
	sf::RenderWindow window(sf::VideoMode(650, 650), "Alien Santa and the Zombie Elf UFO Apocalypse Chimney Bonanza");
	window.setFramerateLimit(60.0f);
	sf::View fixed = window.getView();

	Input input;

	bool bGameOver = false;
	bool bWin = false;

	Game game(&window, &input, &bWin);
	sf::Clock time;

	// Run the program if the window is open. 
	while (window.isOpen() && !bGameOver)
	{
		window.setView(fixed);
		bGameOver = game.update(time.getElapsedTime().asMilliseconds());
		game.render();
		
		// Event handling:
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
			case sf::Event::MouseMoved:
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					input.setMouseLeft(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					input.setMouseLeft(false);
				}
				break;
			default:
				// Don't handle other events. 
				break;
			}
		}

		

		// To quit the game.
		if (input.isKeyDown(sf::Keyboard::Escape))
		{
			window.close();
			die(false);
		}
		// To win the game. 
		if (bWin == true) {
			window.close();
			die(true);
		}
		// To lose the game. 
		if (bGameOver == true) {
			window.close();
			die(false);
		}
	}
	return 0;
}

