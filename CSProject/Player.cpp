#include "Player.h"
#include "GameState.h"
#include "Maths.h"
#include "AssetManager.h"

#include <iostream>

Player::Player(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture) :
	Entity(position, scale, texture),
	m_terrain_height(position.y)
{
	game_timer.restart();
}

Player::~Player() {}

void Player::Update(GameState* state, double dt)
{
	Move(state, (float) dt);
	EntityCollisions(state);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		Attack(state, UP);
}

void Player::Attack(GameState* state, sf::Vector2f direction)
{
	// Request current time since clock was restarted
	attack_time = attack_timer.getElapsedTime().asSeconds();

	// Check if attack time exceeds cooldown
	if (attack_time > 1)
	{
		attack_timer.restart();

		// Set spawn position of Bullet
		sf::Vector2f sprite_centre = this->GetPosition() +
			sf::Vector2f(this->GetSprite().getGlobalBounds().width, this->GetSprite().getGlobalBounds().height) / 2.f;

		sf::Vector2f spawn_pos = sprite_centre + 50.f * direction;
		sf::Vector2f velocity = direction * 800.f + sf::Vector2f(this->GetVelocity().x, 0) * 2.f;

		// Create new bullet and fire towards cursor from player
		state->GetBullets()->push_back(Bullet(spawn_pos, sf::Vector2f(0.02f, 0.02f), AssetManager::m_textures[AssetManager::BALL]));
		state->GetBullets()->back().SetVelocity(velocity.x, velocity.y);
	}
}

void Player::EntityCollisions(GameState* state)
{
	//std::list<Enemy>* enemies = state->GetEnemies();

	//// Loop through list of enemies
	//for (auto &&e : *enemies)
	//{
	//	// Check for intersection between enemy and player
	//	if (this->GetBounds().intersects(e.GetBounds()))
	//	{
	//		this->m_health = 0;
	//	}
	//}
}

void Player::Move(GameState* state, float dt)
{
	// Check key pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		Accelerate(m_velocity.x, -1, dt);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		Accelerate(m_velocity.x, 1, dt);
	else
	{
		// Apply friction opposing movement if player is moving
		if (abs(m_velocity.x) > 0)
			m_velocity.x += m_friction * (-m_velocity.x / abs(m_velocity.x)) * dt;

		// Stop player if velocity below minimum for movement
		if (abs(m_velocity.x) < m_min_vel)
			m_velocity.x = 0;
	}

	// Apply gravity ALWAYS
	//m_velocity.y += m_gravity * dt;
	m_velocity.y += m_gravity * (m_fall_mult - 1) * dt;

	// Check key is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (m_grounded)
		{
			// Apply impulse to jump
			m_velocity.y += -m_acceljump;
			// Player is no longer grounded
			m_grounded = false;
			AssetManager::m_sounds[AssetManager::JUMP].play();
		}
		else if (m_velocity.y < 0)
		{
			m_velocity.y -= m_gravity * (m_jump_mult - 1) * dt;
		}
	}

	// Fix for error causing start glitch
	if (dt > 0.1)
		m_velocity.y = 0;

	// Apply velocity onto position
	m_position += m_velocity * static_cast<float>(dt);

	// Update sprite with new displacement
	m_sprite.setPosition(m_position);
}

void Player::Accelerate(float& velocity, int direction, float dt)
{
	// Check if moving in direction desired or stationary
	if (velocity <= 0)
		// Apply acceleration (from walk force and friction)
		velocity += (m_accelwalk - m_friction) * direction * dt;
	else
		// Apply exaggerated acceleration to change direction more quickly
		velocity += (m_accelwalk + m_accelwalk * m_react - m_friction) * direction * dt;

	// Check if new velocity doesn't exceed max
	if (abs(velocity) > m_max_vel)
		// Limit to max velocity
		velocity = m_max_vel * direction;
}

void Player::SetTerrainHeight(float h)
{
	m_terrain_height = h;
}