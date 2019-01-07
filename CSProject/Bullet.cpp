#include "Bullet.h"
#include "GameState.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture) :
	Entity(position, scale, texture)
{
}

Bullet::~Bullet()
{
}

void Bullet::Update(GameState* state, double dt)
{
	// Bullets fall with gravity
	m_velocity.y += m_gravity * (float) dt;
	m_position += m_velocity * (float) dt;

	// Bullets set to despawn if they hit ground level
	if (m_position.y - this->GetBounds().height >= state->GetPlayer()->GetTerrainHeight() + 30)
	{
		if (!m_ground)
		{
			m_ground = true;
			m_velocity.y = -m_velocity.y * 0.9;
			m_collisions += 1;
		}
	}
	else
	{
		m_ground = false;
	}
	
	if (m_collisions > 3)
		this->SetDespawn(true);

	m_sprite.setPosition(m_position);
}