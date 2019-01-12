#include "Bomb.h"

Bomb::Bomb(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture) :
	Entity(position, scale, texture)
{
}

void Bomb::Update(GameState* state, float dt)
{
	m_velocity.y += m_gravity * dt;
	m_position += m_velocity * dt;
	m_sprite.setPosition(m_position);

	if (m_position.y > 900)
		m_despawn = true;
}
