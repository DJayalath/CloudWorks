#pragma once

#include "ProgramState.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Bullet.h"
#include "AssetManager.h"
#include "EnemyManager.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

class Engine;

class GameState : public ProgramState
{
public:

	GameState();

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(Engine* engine);
	void Update(Engine* engine, double dt);
	void Draw(Engine* engine);

	Player* GetPlayer();
	Camera* GetCamera() { return &m_camera; }
	std::list<Bullet>* GetBullets() { return &m_bullets; }
	std::list<Enemy>* GetEnemies() { return &m_enemies; }
	double GetDeltaTime() { return m_dt; }
	AssetManager* GetAssets() { return &m_assets; }

private:

	AssetManager m_assets;
	sf::Sprite m_sp_background;
	sf::Texture m_tex_background;

	EnemyManager m_enemy_manager;
	std::list<Bullet> m_bullets;
	std::list<Enemy> m_enemies;

	double m_dt;
	Player m_player;
	Camera m_camera;

	bool m_pause = false;

};

