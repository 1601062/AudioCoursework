#include <SFML/Graphics.hpp>

#pragma once
class GameObject :
	public sf::Sprite
{
public:
	GameObject();

	inline sf::Vector2f getVelocity() { return velocity; };
	inline void setVelocity(sf::Vector2f newVelocity) { velocity = newVelocity; };

	void update();

protected:


private:
	sf::Vector2f velocity = { 0, 0 };

};

