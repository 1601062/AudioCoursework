#include "Player.h"

Player::Player()
{
	//
	playerTexture.loadFromFile("gfx/Santa.png");
	setTexture(playerTexture);
	setOrigin(72, 72);
	setPosition(325, 325);
	setScale(1.0f, 1.0f);
}

sf::Vector2f Player::getLastVelocity()
{
	return lastVelocity;
}

void Player::update()
{
	GameObject::update();
	if (getVelocity() != sf::Vector2f(0.0f, 0.0f))
	lastVelocity = getVelocity();
}