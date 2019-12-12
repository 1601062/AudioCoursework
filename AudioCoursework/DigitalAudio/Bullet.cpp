#include "Bullet.h"

Bullet::Bullet(sf::Vector2f firingPosition, sf::Vector2f firingDirection, sf::Texture* bulletTexture)
{
	//
	setTexture(*bulletTexture);
	setOrigin(25, 25);
	setScale(0.25f, 0.25f);
	setPosition(firingPosition);
	setVelocity(firingDirection);
}

Bullet::~Bullet() {
	bulletTexture = 0;
	delete bulletTexture;
}