#pragma once

#include "Entity.h"
class Bullet :
	public Entity
{
public:
	Bullet(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture);
	~Bullet();

	bool GetDespawn() { return m_despawn; }
	void SetDespawn(bool state) { m_despawn = state; }
	void Update(GameState* state, float dt) override;

	void GroundCollision(float intersect_height)
	{
		m_position.y -= intersect_height;
		m_velocity.y = -m_velocity.y * 0.9f;
		m_collisions += 1;
	}

private:

	bool m_despawn = false;
	bool m_ground = false;
	const float m_gravity = 1000.f;
	int m_collisions = 0;
};

