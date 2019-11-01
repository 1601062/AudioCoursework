#include "Game.h"

Game::Game(sf::RenderWindow* win) : window(win) {
	//
	BgTexture.loadFromFile("gfx/Background.png");
	Background.setTexture(BgTexture);

	//
	P1Texture.loadFromFile("gfx/p1.png");
	Player1.setTexture(P1Texture);
	Player1.setOrigin(40, 40);
	Player1.setPosition(250, 325);
	Player1.setVelocity(sf::Vector2f(1.0f, 1.0f));

	//
	P2Texture.loadFromFile("gfx/p2.png");
	Player2.setTexture(P2Texture);
	Player2.setOrigin(40, 40);
	Player2.setPosition(400, 325);
}

void Game::update(float dt)
{
	Player1.update();
	Player2.update();
}

void Game::render()
{
	window->clear(sf::Color::Black);

	window->draw(Background);
	window->draw(Player1);
	window->draw(Player2);

	window->display();
}
