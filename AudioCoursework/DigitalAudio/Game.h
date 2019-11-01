#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//
#include "GameObject.h"

#pragma once
class Game
{
public:
	Game(sf::RenderWindow* window);

	void update(float dt);
	void render();

protected:


private:
	// window reference
	sf::RenderWindow* window;

	//
	GameObject Background;
	sf::Texture BgTexture;

	//
	GameObject Player1;
	sf::Texture P1Texture;

	//
	GameObject Player2;
	sf::Texture P2Texture;
};

