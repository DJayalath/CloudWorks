#pragma once

// Required for Sprites, Textures and Vector structure
#include "Entity.h"
#include <list>

class Enemy;
class Player : public Entity
{
public:

	/* Player requires a starting x and y
	co-ordinate for initialization */
	Player(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture);
	~Player();

	// Set Requests
	void SetTerrainHeight(float h);
	float GetTerrainHeight() { return m_terrain_height; }

	// Procedure for frame-by-frame updates
	void Update(GameState* state, double dt) override;
	int& EnemiesKilled() { return enemies_killed; }
	int GetTime() { return game_timer.getElapsedTime().asSeconds(); }

private:

	void Move(float dt);
	void EntityCollisions(GameState* state);
	void Attack(GameState* state);

	void Accelerate(float& velocity, int direction, float dt);

	// Physics Constants
	const float m_accelwalk = 8000.f;
	const float m_friction = 3000.f;
	const float m_react = 0.5f;
	const float m_max_vel = 250.f;
	const float m_min_vel = 10.f;
	float m_proj_vel = 0;
	int enemies_killed = 0;


	const float m_acceljump = 650.f;
	const float m_gravity = 1500.f;


	// Misc.
	bool m_grounded = true;
	float m_terrain_height;
	sf::Clock damage_timer;
	float damage_time;
	sf::Clock attack_timer;
	sf::Clock game_timer;
	float attack_time;

};