#pragma once

#include "ProgramState.h"
#include "Player.h"
#include "Camera.h"
#include "Bullet.h"
#include "Bomber.h"
#include "Bomb.h"
#include "Spike.h"
#include "AssetManager.h"
#include "TerrainGenerator.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
	std::vector<Bomb>& GetBombs() { return m_bombs; }
	AssetManager& GetAssets() { return m_assets; }

private:

	AssetManager m_assets;
	sf::Sprite m_sp_background;
	sf::Texture m_tex_background;

	std::list<Bullet> m_bullets;
	std::vector<Bomber> m_bombers;
	std::vector<Bomb> m_bombs;
	std::vector<Spike> m_spikes;

	sf::Clock m_timer;
	float m_time;

	Player m_player;
	Camera m_camera;

	bool m_pause = false;

	TerrainGenerator m_terrain_generator;
	std::list<Plank> m_chunks;

};

