#include "Player.h"
#include "GameState.h"
#include "Maths.h"
#include "AssetManager.h"

#include <iostream>

Player::Player(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture) :
	Entity(position, scale, texture)
{
	game_timer.restart();
}

Player::~Player() {}

void Player::Update(GameState* state, float dt)
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
	m_position += m_velocity * dt;

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