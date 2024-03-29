#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

#pragma once
class Player :
	public GameObject
{
public:
	Player();
	sf::Vector2f getLastVelocity();

	virtual void update();

protected:

private:
	sf::Texture playerTexture;
	sf::Vector2f lastVelocity;
};
