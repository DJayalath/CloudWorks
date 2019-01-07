#include "Entity.h"

Entity::Entity(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture) :
	m_position(position),
	m_health(100)
{
	m_sprite.setTexture(texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(scale);
}

Entity::~Entity() {}

void Entity::SetPosition(float x, float y)
{
	m_position = sf::Vector2f(x, y);
}

void Entity::SetVelocity(float v_x, float v_y)
{
	m_velocity = sf::Vector2f(v_x, v_y);
}

sf::Sprite& Entity::GetSprite()
{
	return m_sprite;
}

sf::FloatRect Entity::GetBounds()
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Entity::GetPosition()
{
	return m_position;
}

sf::Vector2f Entity::GetVelocity()
{
	return m_velocity;
}

float Entity::GetHealth()
{
	return m_health;
}
