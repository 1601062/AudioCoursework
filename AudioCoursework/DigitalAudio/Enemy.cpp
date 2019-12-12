#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(sf::Vector2f startPosition, sf::Vector2f flyingDirection, sf::Texture* enemyTexture)
{
	//
	setTexture(*enemyTexture);
	setOrigin(59.0f, 83.0f);
	setPosition(startPosition);
	setVelocity(flyingDirection);
}

void Enemy::update()
{
	GameObject::update();
}