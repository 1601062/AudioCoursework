#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
class Bullet :
	public GameObject
{
public:
	Bullet(sf::Vector2f firingPosition, sf::Vector2f firingDirection, sf::Texture* bulletTexture);
	~Bullet();

protected:

private:
	sf::Texture* bulletTexture;
};

