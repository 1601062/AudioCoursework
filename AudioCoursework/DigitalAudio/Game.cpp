#include "Game.h"

Game::Game(sf::RenderWindow* win, Input* in) : window(win), input(in) {
	//
	BgTexture.loadFromFile("gfx/Background.png");
	Background.setTexture(BgTexture);

	//
	Santa.setOrigin(400, 400);
	Santa.setPosition(125, 550);
	Santa.setScale(0.25f, 0.25f);

	//
	AudioInit();
}

void Game::AudioInit() {
	cowbell = new Audio("quiet_Cowbell.wav");
	cymbal = new Audio("cra_Rock_a.wav");
	backwards_cymbal = new Audio("cra_Rock_a.wav");

	// Cowbell effects
	cowbell->Normalize();
	cowbell->Reverse();
	cowbell->Delay(5, 100, 0.9);
	// Cymbal effects
	cymbal->Normalize();
	cymbal->Delay(5, 0.3, 0.5);
	// Backwards cymbal effects
	backwards_cymbal->Normalize();
	backwards_cymbal->Reverse();
	backwards_cymbal->Combine(cymbal->GetSamples());
	backwards_cymbal->Normalize();
};

void Game::update(float dt)
{
	float runmult = 1.0f;
	if (input->isKeyDown(sf::Keyboard::LShift)) {
		runmult = 2.0f;
	}

	if (input->isKeyDown(sf::Keyboard::A)) {
		Santa.setVelocity(sf::Vector2f(-15.0f * runmult, 0.0f));
	} else if (input->isKeyDown(sf::Keyboard::D)) {
		Santa.setVelocity(sf::Vector2f(15.0f * runmult, 0.0f));
	}
	else {
		Santa.setVelocity(sf::Vector2f(0.0f, 0.0f));
	}

	Santa.update();

	//cymbal->PlayAudio();
}

void Game::render()
{
	window->clear(sf::Color::Black);

	window->draw(Background);
	window->draw(Santa);

	window->display();
}
