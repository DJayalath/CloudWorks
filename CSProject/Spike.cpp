#include "Spike.h"
#include "GameState.h"

Spike::Spike(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture) :
	Entity(position, scale, texture)
{
	// Set default velocity
	m_velocity.x = -100.f;
}

void Spike::Update(GameState* state, float dt)
{
	// Apply gravity to velocity
	m_velocity.y += m_gravity * dt;
	// Add velocity to position
	m_position += m_velocity * dt;
	// Update sprite displacement
	m_sprite.setPosition(m_position);
	// Test if Spike moves off screen and should be erased
	if (m_position.x < state->GetPlayer()->GetPosition().x - 1280 || m_position.y > 900)
		m_despawn = true;
}

