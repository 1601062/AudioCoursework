#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

#pragma once
class Enemy :
	public GameObject
{
public:
	Enemy();
	Enemy(sf::Vector2f startPosition, sf::Vector2f flyingDirection, sf::Texture* enemyTexture);

	virtual void update();

protected:

private:
	sf::Texture enemyTexture;
	
};
