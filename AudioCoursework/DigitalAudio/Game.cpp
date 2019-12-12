#include "Game.h"
#include <random>
#include <time.h>

using std::cerr;

void Game::die(const char* s) {
	cerr << "Fatal: " << s << "\n";
	cerr << "Current directory is:\n";
	system("cd");
	system("pause");
	exit(1);
}

Game::Game(sf::RenderWindow* win, Input* in, bool* bWin) : window(win), input(in), bGameWon(bWin) {
	//
	bgTexture.loadFromFile("gfx/Background.png");
	background.setTexture(bgTexture);

	//
	enemyTexture.loadFromFile("gfx/BadElf.png");
	enemies_vector.push_back(new Enemy(sf::Vector2f(750, 750), sf::Vector2f(1.0f, 1.0f), &enemyTexture));

	//
	bulletTexture.loadFromFile("gfx/Bullet.png");

	//
	shootClock = new sf::Clock();
	spawnClock = new sf::Clock();

	//
	AudioInit();

	//
	srand(time(NULL));
}

void Game::AudioInit() {
	shoot_sfx = new Audio("sfx/shoot.wav");
	hohoho_sfx = new Audio("sfx/hohoho.ogg");
	elf_sfx_boom = new Audio("sfx/explosion.wav");

	// Shoot effects
	shoot_sfx->Normalize();					// First, let's normalize the sound to deal with any potential clipping
	shoot_sfx->Amplify(1.0);				// It's a bit loud still, so amplify by a factor of 0.75 to decrease volume
	//shoot_sfx->Delay(3, 0.2, 0.5);			// Delete comment to enable some echo - arguments control echo properties

	// Elf explosion effects (part one)
	hohoho_sfx->Normalize();				// Normalize for balanced audio. 
	hohoho_sfx->Delay(5, 0.5, 0.85);

	// Elf explosion effects (part two)
	elf_sfx_boom->Normalize();				// Normalize for balanced audio. 

	//
	if (!music.openFromFile("sfx/jingle.ogg"))
		die("loading failed");

	music.play();
	music.setLoop(true);
};

bool Game::update(float dt)
{
	// God and test modes for marking or insanity - caution: don't turn off god mode in test mode:
	HandleModes();
	// Santa movement logic:
	SantaMove();
	// Santa firing logic:
	HandleAttacks(0.1f);
	// Enemy spawn logic:
	HandleEnemies(spawnTime);
	// Spawn timing logic - spawning time interval decreases until interval is 0.25 seconds between spawns (use test mode to speed things up):
	if (spawnTime > 0.25f) {
		spawnTime -= 0.0003;
	}
	// Win logic:
	if (g_factor <= 0.15f && SantaInCentre()) {
		music.pause();					// Pause the music.
		hohoho_sfx->Play();				// Play the winning sound effect. 
		sf::sleep(sf::seconds(5));		// Pause for dramatic effect. 
		*bGameWon = true;				// Set win bool to true!
	}

	// Returns true when santa is dead:
	return bGameOver;
}

void Game::HandleModes()
{
	// God mode stuff.
	if (input->isKeyDown(sf::Keyboard::G) && !bGodMode) {
		std::cout << "God mode enabled." << std::endl;
		bGodMode = true;
		sf::sleep(sf::milliseconds(500));
	}
	else if (input->isKeyDown(sf::Keyboard::G) && bGodMode) {
		std::cout << "God mode disabled." << std::endl;
		bGodMode = false;
		sf::sleep(sf::milliseconds(500));
	}
	// Test mode stuff. 
	if (input->isKeyDown(sf::Keyboard::T) && !bTestMode) {
		std::cout << "God mode enabled." << std::endl;
		std::cout << "Test mode enabled." << std::endl;
		bTestMode = true;
		bGodMode = true;
		spawnTime = 0.125f;
		sf::sleep(sf::milliseconds(500));
	}
	else if (input->isKeyDown(sf::Keyboard::T) && bTestMode) {
		std::cout << "Test mode disabled." << std::endl;
		bTestMode = false;
		spawnTime = 0.25f;
		sf::sleep(sf::milliseconds(500));
	}
}

bool Game::SantaInCentre() {
	// Simple function for checking if Santa is in the centre of the screen.
	return (Santa.getPosition().x < 335 && Santa.getPosition().x > 315 && Santa.getPosition().y < 335 && Santa.getPosition().y > 315);
}

void Game::HandleAttacks(float interval)
{
	sf::Time t = shootClock->getElapsedTime();
	if (t.asSeconds() > interval) {
		// Get Santa position
		sf::Vector2f santaPos = Santa.getPosition();
		// Get Mouse position
		sf::Vector2f mousePos = sf::Vector2f(input->getMouseX(), input->getMouseY());
		// Create bullet direction
		sf::Vector2f bulletDir = Normalize(mousePos - santaPos) * 10.0f;

		// When left mouse is pressed:
		if (input->getMouseLeft() == true) {
			bullets_vector.push_back(new Bullet(santaPos, bulletDir, &bulletTexture));	// Shoot.
			bullets_vector.back()->setScale(g_factor, g_factor);
			shoot_sfx->Play();															// Shoot sound effect. 
		}

		shootClock->restart();
	}

	// Delete off-screen bullets
	for (int i = bullets_vector.size() - 1; i >= 0; i--) {
		if (BulletLost(i)) {
			bullets_vector.erase(bullets_vector.begin() + i);
		}
	}

	// Update remaining bullets
	for (int i = bullets_vector.size() - 1; i >= 0; --i) {
		bullets_vector[i]->update();
	}
}

sf::Vector2f Game::Normalize(sf::Vector2f targetVec)
{
	// Simple function for normalizing a vector to be used for shooting directions etc...
	float length = sqrt((targetVec.x * targetVec.x) + (targetVec.y * targetVec.y));
	if (length != 0)
		return sf::Vector2f(targetVec.x / length, targetVec.y / length);
	else
		return targetVec;
}

bool Game::BulletLost(int i)
{
	// Simple function to check if bullet has left the screen. 
	return bullets_vector[i]->getPosition().x < -25.0f || bullets_vector[i]->getPosition().x > 675.0f || bullets_vector[i]->getPosition().y < -25.0f || bullets_vector[i]->getPosition().y > 675.0f;
}

void Game::HandleEnemies(float interval) {
	sf::Time t = spawnClock->getElapsedTime();
	if (t.asSeconds() > interval) {
		// Create a spawn location outside walls
		sf::Vector2f randomSpawnPoint = GetSpawnPoint();
		// Get Santa position
		sf::Vector2f santaPos = Santa.getPosition();
		// Create enemy direction
		sf::Vector2f enemyDir = Normalize(santaPos - randomSpawnPoint);
		//
		enemies_vector.push_back(new Enemy(randomSpawnPoint, (enemyDir * 2.5f), &enemyTexture));
		enemies_vector.back()->setScale(g_factor, g_factor);
		//
		spawnClock->restart();
	}

	// Delete off-screen enemies
	for (int i = enemies_vector.size() - 1; i >= 0; i--) {
		if (EnemyLost(i)) {
			enemies_vector.erase(enemies_vector.begin() + i);
		}
	}

	// Update remaining enemies
	for (int i = enemies_vector.size() - 1; i >= 0; --i) {
		enemies_vector[i]->update();	// Update the game object first. 

		if (DetectCollision(&(GameObject)Santa, enemies_vector[i]) && !bGodMode) {
			bGameOver = true;			// If an enemy reaches Santa, game over!
		}

		for (int j = bullets_vector.size() - 1; j >= 0; j--) {				// For all the bullets...

			if (DetectCollision(enemies_vector[i], bullets_vector[j])) {	// If any bullet collides with the current enemy:

				elf_sfx_boom->Reset();			// Reset the sound or it will get quieter each time!
				elf_sfx_boom->Amplify(0.5f);	// Dial it down a little, sound is too loud. 

				float distance = CalculateDistance(&(GameObject)Santa, enemies_vector[i]);	// Calculate the distance between Santa and his elf...
				elf_sfx_boom->DistanceAttenuation(g_factor, 1);							// Distance based attenuation. 
				
				elf_sfx_boom->Play();			// Boom

				enemies_vector.erase(enemies_vector.begin() + i);			// Destroy enemy. 
				j = 0;														// End loop. 

				g_factor *= 0.99f;
				Santa.setScale(g_factor, g_factor);
				pitch_ *= 1.005f;
				music.setPitch(pitch_);
				std::cout << g_factor << std::endl;
			}
		}
	}
}

sf::Vector2f Game::GetSpawnPoint()
{
	// Function for selecting random spawn points for enemies. 

	int randomSide = rand() % 4; // 0 left, 1 up, 2 right, 3 down
	float x = 0;
	float y = 0;
	switch (randomSide) {
	case 0:
		x = -200;
		y = rand() % 850 + -200;
		break;
	case 1:
		x = rand() % 850 + -200;
		y = -200;
		break;
	case 2:
		x = 850;
		y = rand() % 850 + -200;
		break;
	case 3:
		x = rand() % 850 + -200;
		y = 850;
		break;
	}
	return sf::Vector2f(x, y);
}

bool Game::EnemyLost(int i)
{
	// Simple function for checking if enemy is off the screen. 
	return enemies_vector[i]->getPosition().x < -500.0f || enemies_vector[i]->getPosition().x > 1150.0f || enemies_vector[i]->getPosition().y < -500.0f || enemies_vector[i]->getPosition().y > 1150.0f;
}

void Game::SantaMove()
{
	// Function handles all Santa movement.
	float runmult = 1.0f;
	if (input->isKeyDown(sf::Keyboard::LShift)) {	// "Boost"
		runmult = 2.5f;
	}

	sf::Vector2f inputVector{ 0.0f, 0.0f };			// Movement based on input vector
	if (input->isKeyDown(sf::Keyboard::A) && !WallCheck(0, &(GameObject)Santa)) {
		inputVector += sf::Vector2f(-2.0f * runmult, 0.0f);
	}
	if (input->isKeyDown(sf::Keyboard::D) && !WallCheck(2, &(GameObject)Santa)) {
		inputVector += sf::Vector2f(2.0f * runmult, 0.0f);
	}
	if (input->isKeyDown(sf::Keyboard::S) && !WallCheck(3, &(GameObject)Santa)) {
		inputVector += sf::Vector2f(0.0f, 2.0f * runmult);
	}
	if (input->isKeyDown(sf::Keyboard::W) && !WallCheck(1, &(GameObject)Santa)) {
		inputVector += sf::Vector2f(0.0f, -2.0f * runmult);
	}

	Santa.setVelocity(inputVector);

	Santa.update();
}

bool Game::WallCheck(int wall_num, GameObject* go) {
	// Function for checking if an object is colliding with wall bounds. 
	switch (wall_num) {
	case 0: //left
		if (go->getPosition().x <= 0) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 1: //up
		if (go->getPosition().y <= 0) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 2: //right
		if (go->getPosition().x >= 650) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 3: //down
		if (go->getPosition().y >= 650) {
			return true;
		}
		else {
			return false;
		}
		break;
	}
}

void Game::render()
{
	// Renders everything...
	window->clear(sf::Color::Black);
	window->draw(background);
	window->draw(Santa);
	for (int i = 0; i < bullets_vector.size(); i++) {
		window->draw(*bullets_vector.at(i));
	}
	for (int i = 0; i < enemies_vector.size(); i++) {
		window->draw(*enemies_vector.at(i));
	}
	window->display();
}

bool Game::DetectCollision(GameObject* go1, GameObject* go2)
{
	// Bounding box based collision detection.

	sf::FloatRect go1Bounds = go1->getLocalBounds();
	sf::FloatRect go2Bounds = go2->getLocalBounds();
	// Bounding box collision
	if (go1->getPosition().x < go2->getPosition().x + go2Bounds.width/2 &&
		go1->getPosition().x + go1Bounds.width/2 > go2->getPosition().x &&
		go1->getPosition().y < go2->getPosition().y + go2Bounds.height/2 &&
		go1->getPosition().y + go2Bounds.height/2 > go2->getPosition().y)
		return true;

	return false;
}

float Game::CalculateDistance(GameObject* go1, GameObject* go2) {
	// Function for distance calculations. 
	float distance = 
		(abs(sqrt(((go1->getPosition().x - go2->getPosition().x) * (go1->getPosition().x - go2->getPosition().x))
		+ ((go1->getPosition().y - go2->getPosition().y) * (go1->getPosition().y - go2->getPosition().y)))));

	return distance;
}