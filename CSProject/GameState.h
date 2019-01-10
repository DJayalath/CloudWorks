#pragma once

#include "ProgramState.h"
#include "Player.h"
#include "Camera.h"
#include "Bullet.h"
#include "Bomber.h"
#include "Bomb.h"
#include "Spike.h"
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

private:

	// Set background
	sf::Sprite m_sp_background;
	sf::Texture m_tex_background;

	// Vectors/Lists of entities
	std::list<Bullet> m_bullets;
	std::vector<Bomber> m_bombers;
	std::vector<Bomb> m_bombs;
	std::vector<Spike> m_spikes;
	std::list<Plank> m_chunks;
	// Single player entity
	Player m_player;

	// Game timer
	sf::Clock m_timer;
	float m_time;

	// Game camera
	Camera m_camera;
	// Terrain generator
	TerrainGenerator m_terrain_generator;

};

