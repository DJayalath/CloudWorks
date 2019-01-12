#pragma once
#include "Entity.h"
class Spike :
	public Entity
{
public:
	Spike(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture);
	void Update(GameState* state, float dt) override;
	void GroundCollision(float intersection_height)
	{
		m_position.y -= intersection_height;
		m_velocity.y = 0;
	}
private:
	float m_gravity = 500;
};

