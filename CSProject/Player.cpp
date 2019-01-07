#include "Player.h"
#include "Enemy.h"
#include "GameState.h"
#include "Maths.h"

#include <iostream>

Player::Player(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture) :
	Entity(position, scale, texture),
	m_terrain_height(position.y)
{}

Player::~Player() {}

void Player::Update(GameState* state, double dt)
{
	Move((float) dt);
	EntityCollisions(state);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Attack(state);
}

void Player::Attack(GameState* state)
{
	// Request current time since clock was restarted
	attack_time = attack_timer.getElapsedTime().asSeconds();

	// Check if attack time exceeds cooldown
	if (attack_time > 0.5)
	{
		attack_timer.restart();
		
		// Correct player position to be relative to cursor position by subtracting camera distance
		float player_x = this->GetPosition().x - (state->GetCamera()->GetCentre().x - 640);
		sf::Vector2f player_pos_relative = sf::Vector2f(player_x, this->GetPosition().y);

		// Calculate direction vector towards cursor from player
		sf::Vector2f player_to_cursor = Maths::GetUnitVec(sf::Vector2f(1,1));

		// Set spawn position of Bullet
		sf::Vector2f spawn_pos = sf::Vector2f(this->GetPosition().x + 50, this->GetPosition().y - 10);

		// Create new bullet and fire towards cursor from player
		state->GetBullets()->push_back(Bullet(spawn_pos, sf::Vector2f(0.02f, 0.02f), state->GetAssets()->texture_map.at("Ball")));
		state->GetBullets()->back().SetVelocity((player_to_cursor.x) * 250 + this->GetVelocity().x, (player_to_cursor.y) * 500 + this->GetVelocity().y);
	}
}

void Player::EntityCollisions(GameState* state)
{
	std::list<Enemy>* enemies = state->GetEnemies();

	// Loop through list of enemies
	for (auto &&e : *enemies)
	{
		// Check for intersection between enemy and player
		if (this->GetBounds().intersects(e.GetBounds()))
		{
			this->m_health = 0;

			//// Get elapsed time each collision
			//damage_time = damage_timer.getElapsedTime().asSeconds();

			//// Check if damage time exceeds cooldown
			//if (damage_time > 0.25)
			//{
			//	// Restart clock if damaged
			//	damage_timer.restart();
			//	// Damage player
			//	m_health -= 5;
			//	// Set player to damage colour
			//	m_sprite.setColor(sf::Color::Red);
			//}

		}
		// Check if sprite is in damage colour
		else if (m_sprite.getColor() == sf::Color::Red)
			// Reset to normal colour
			m_sprite.setColor(sf::Color::White);
	}
}

void Player::Move(float dt)
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

	if (m_grounded)
	{
		// Check key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			// Apply impulse to jump
			m_velocity.y += -m_acceljump;
			// Player is no longer grounded
			m_grounded = false;
		}
	}
	else
	{
		// Apply gravity
		m_velocity.y += m_gravity * dt;

		// Check if player falls below ground height
		if (m_position.y > m_terrain_height)
		{
			// Cancel all vertical velocity
			m_velocity.y = 0;
			// Set player to ground height
			m_position.y = m_terrain_height;
			// Player is now fixed on ground
			m_grounded = true;
		}
	}

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