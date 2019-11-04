#include "GameObject.h"
#include <SFML/Graphics.hpp>

#pragma once
class Player :
	public GameObject
{
public:
	Player();

	void update();
	void animate(int direction, int speed);

protected:

private:
	sf::Texture* WalkTextures[11];
	sf::Texture* RunTextures[13];
	sf::Texture* IdleTextures[16];
	int frameSpeed = 3; // frames per animation
	int currentFrameProgress = 0;

	int lastFrameDir = 2;
	int animFrameNum = 0;
	int maxAnimFrameNum = 15;
	int lastSpeed = 0;
};
