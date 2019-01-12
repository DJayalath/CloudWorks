#include "Bullet.h"
#include "GameState.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture) :
	Entity(position, scale, texture)
{
}

Bullet::~Bullet()
{
}

void Bullet::Update(GameState* state, float dt)
{
	// Bullets fall with gravity
	m_velocity.y += m_gravity * (float) dt;
	m_position += m_velocity * (float) dt;

	if (this->GetPosition().y > 800 || this->GetPosition().y < -100 ||
		this->GetPosition().x > state->GetCamera()->GetCentre().x + 800 ||
		this->GetPosition().x < state->GetCamera()->GetCentre().x - 800)
		m_despawn = true;

	m_sprite.setPosition(m_position);
}