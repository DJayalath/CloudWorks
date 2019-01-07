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
	void Update(GameState* state, double dt) override;

private:

	bool m_despawn = false;
	bool m_ground = false;
	const float m_gravity = 2000.f;
	int m_collisions = 0;
};

