#pragma once
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//
#include "GameObject.h"
#include "Player.h"
#include "Bullet.h"
#include "Audio.h"
#include "Input.h"
#include "Enemy.h"

#pragma once
class Game
{
public:
	
	Game(sf::RenderWindow* window, Input* in, bool* bWin);
	
	void AudioInit();
	bool update(float dt);
	void HandleModes();
	bool SantaInCentre();
	void HandleAttacks(float interval);
	sf::Vector2f Normalize(sf::Vector2f targetVec);
	bool BulletLost(int i);
	void HandleEnemies(float interval);
	sf::Vector2f GetSpawnPoint();
	bool EnemyLost(int i);
	void SantaMove();
	bool WallCheck(int wall_num, GameObject* go);
	void render();

	bool DetectCollision(GameObject* go1, GameObject* go2);

	float CalculateDistance(GameObject* go1, GameObject* go2);


protected:


private:
	// for timing
	sf::Clock* shootClock;
	//
	sf::Clock* spawnClock;
	float spawnTime = 1.5f;

	// window reference
	sf::RenderWindow* window;
	Input* input;

	//
	GameObject background;
	sf::Texture bgTexture;

	//
	std::vector<Enemy*> enemies_vector;
	sf::Texture enemyTexture;


	//
	Player Santa;

	//
	Audio* shoot_sfx;
	Audio* hohoho_sfx;
	Audio* elf_sfx_boom;
	sf::Music music;

	//
	std::vector<Bullet*> bullets_vector;
	sf::Texture bulletTexture;

	//
	bool bGameOver = false;
	bool* bGameWon = nullptr;
	bool bGodMode = false;
	bool bTestMode = false;

	//
	float g_factor = 1.0f;
	float pitch_ = 1.0f;

	//
	void die(const char* s);
};

