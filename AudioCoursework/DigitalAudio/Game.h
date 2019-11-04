#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//
#include "GameObject.h"
#include "Player.h"
#include "Audio.h"
#include "Input.h"

#pragma once
class Game
{
public:
	Game(sf::RenderWindow* window, Input* in);

	void update(float dt);
	void render();
	void AudioInit();

protected:


private:
	// window reference
	sf::RenderWindow* window;
	Input* input;

	//
	GameObject Background;
	sf::Texture BgTexture;

	//
	Player Santa;

	//
	Audio* cowbell;
	Audio* cymbal;
	Audio* backwards_cymbal;
};

