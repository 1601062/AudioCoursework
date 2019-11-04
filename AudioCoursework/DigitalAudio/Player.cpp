#include "Player.h"

Player::Player()
{
	for (int i = 0; i < 11; i++) {
		RunTextures[i] = new sf::Texture;
	}
	RunTextures[0]->loadFromFile("gfx/Run (1).png");
	RunTextures[1]->loadFromFile("gfx/Run (2).png");
	RunTextures[2]->loadFromFile("gfx/Run (3).png");
	RunTextures[3]->loadFromFile("gfx/Run (4).png");
	RunTextures[4]->loadFromFile("gfx/Run (5).png");
	RunTextures[5]->loadFromFile("gfx/Run (6).png");
	RunTextures[6]->loadFromFile("gfx/Run (7).png");
	RunTextures[7]->loadFromFile("gfx/Run (8).png");
	RunTextures[8]->loadFromFile("gfx/Run (9).png");
	RunTextures[9]->loadFromFile("gfx/Run (10).png");
	RunTextures[10]->loadFromFile("gfx/Run (11).png");
	for (int i = 0; i < 13; i++) {
		WalkTextures[i] = new sf::Texture;
	}
	WalkTextures[0]->loadFromFile("gfx/Walk (1).png");
	WalkTextures[1]->loadFromFile("gfx/Walk (2).png");
	WalkTextures[2]->loadFromFile("gfx/Walk (3).png");
	WalkTextures[3]->loadFromFile("gfx/Walk (4).png");
	WalkTextures[4]->loadFromFile("gfx/Walk (5).png");
	WalkTextures[5]->loadFromFile("gfx/Walk (6).png");
	WalkTextures[6]->loadFromFile("gfx/Walk (7).png");
	WalkTextures[7]->loadFromFile("gfx/Walk (8).png");
	WalkTextures[8]->loadFromFile("gfx/Walk (9).png");
	WalkTextures[9]->loadFromFile("gfx/Walk (10).png");
	WalkTextures[10]->loadFromFile("gfx/Walk (11).png");
	WalkTextures[11]->loadFromFile("gfx/Walk (12).png");
	WalkTextures[12]->loadFromFile("gfx/Walk (13).png");
	for (int i = 0; i < 16; i++) {
		IdleTextures[i] = new sf::Texture;
	}
	IdleTextures[0]->loadFromFile("gfx/Idle (1).png");
	IdleTextures[1]->loadFromFile("gfx/Idle (2).png");
	IdleTextures[2]->loadFromFile("gfx/Idle (3).png");
	IdleTextures[3]->loadFromFile("gfx/Idle (4).png");
	IdleTextures[4]->loadFromFile("gfx/Idle (5).png");
	IdleTextures[5]->loadFromFile("gfx/Idle (6).png");
	IdleTextures[6]->loadFromFile("gfx/Idle (7).png");
	IdleTextures[7]->loadFromFile("gfx/Idle (8).png");
	IdleTextures[8]->loadFromFile("gfx/Idle (9).png");
	IdleTextures[9]->loadFromFile("gfx/Idle (10).png");
	IdleTextures[10]->loadFromFile("gfx/Idle (11).png");
	IdleTextures[11]->loadFromFile("gfx/Idle (12).png");
	IdleTextures[12]->loadFromFile("gfx/Idle (13).png");
	IdleTextures[13]->loadFromFile("gfx/Idle (14).png");
	IdleTextures[14]->loadFromFile("gfx/Idle (15).png");
	IdleTextures[15]->loadFromFile("gfx/Idle (16).png");
}

void Player::update()
{
	if (getVelocity().x == 0.0f) {	// IDLE
		animate(1, 0);
	} else if (getVelocity().x < 0.0f && getVelocity().x >= -15.0f) { // WALK LEFT
		animate(0, 1);
	} else if (getVelocity().x < -15.0f) {	// RUN LEFT
		animate(0, 2);
	} else if (getVelocity().x > 0.0f && getVelocity().x <= 15.0f) {	// WALK RIGHT
		animate(2, 1);
	} else if (getVelocity().x > 15.0f) {	// RUN RIGHT
		animate(2, 2);
	}
}

void Player::animate(int direction, int speed) // left = 0, idle = 1, right = 2
{	
	currentFrameProgress++;
	if (direction != lastFrameDir && direction != 1) {
		scale(-1.0f, 1.0f);
	}

	if (speed != lastSpeed) {
		animFrameNum = 0;
		switch (speed) {
		case 0:
			maxAnimFrameNum = 16;
			break;
		case 1:
			maxAnimFrameNum = 11;
			break;
		case 2:
			maxAnimFrameNum = 13;
			break;
		}
	}

	switch (speed) {
	case 0:
		setTexture(*IdleTextures[animFrameNum]);
		break;
	case 1:
		setTexture(*WalkTextures[animFrameNum]);
		break;
	case 2:
		setTexture(*RunTextures[animFrameNum]);
		break;
	}

	if (currentFrameProgress > frameSpeed) {
		currentFrameProgress = 0;
		if (animFrameNum < maxAnimFrameNum) {
			animFrameNum++;
		}
		else {
			animFrameNum = 0;
		}
	}
	lastSpeed = speed;
	if (direction != 1) {
		lastFrameDir = direction;
	}
}