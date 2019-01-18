#pragma once

// Required for Sprites, Textures and Vector structure
#include "Entity.h"
#include <list>

class Enemy;
class Player : public Entity
{
public:

	Player(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture);
	~Player();

	// Procedure for frame-by-frame updates
	void Update(GameState* state, float dt) override;
	int GetTime() { return static_cast<int>(game_timer.getElapsedTime().asSeconds()); }
	bool& Grounded() { return m_grounded; }

	void SetHealth(float h) { m_health = h; }
	void Accelerate(int direction, float dt);
	void ApplyFriction(float dt);
	void Jump(float dt);

private:

	sf::Vector2f UP = sf::Vector2f(0, -1);
	sf::Vector2f LEFT = sf::Vector2f(-1, 0);
	sf::Vector2f RIGHT = sf::Vector2f(1, 0);
	sf::Vector2f DOWN = sf::Vector2f(0, -1);

	// Physics Constants
	const float m_accelwalk = 8000.f;
	const float m_friction = 3000.f;
	const float m_react = 0.5f;
	const float m_max_vel = 250.f;
	const float m_min_vel = 10.f;
	float m_proj_vel = 0;

	const float m_acceljump = 500.f;
	const float m_gravity = 1500.f;
	const float m_fall_mult = 2.5f;
	const float m_jump_mult = 1.9f;

	// Misc.
	bool m_grounded = true;
	sf::Clock game_timer;

};