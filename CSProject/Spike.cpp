#include "Spike.h"

Spike::Spike(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture) :
	Entity(position, scale, texture)
{
	m_velocity.x = -100.f;
}

void Spike::Update(GameState* state, float dt)
{
	m_velocity.y += m_gravity * dt;
	m_position += m_velocity * dt;
	m_sprite.setPosition(m_position);
}
