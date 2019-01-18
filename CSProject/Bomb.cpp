#include "Bomb.h"

Bomb::Bomb(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture) :
	Entity(position, scale, texture)
{}

void Bomb::Update(GameState* state, float dt)
{
	// Apply default gravity to bomb velocity
	m_velocity.y += m_gravity * dt;
	// Update bomb's position from velocity
	m_position += m_velocity * dt;
	// Update sprite position
	m_sprite.setPosition(m_position);

	// Set flag for despawning to true if bomb
	// falls outside of window bounds (bottom)
	if (m_position.y > 900)
		m_despawn = true;
}
