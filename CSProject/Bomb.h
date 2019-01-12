#pragma once
#include "Entity.h"
class Bomb :
	public Entity
{
public:
	Bomb(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture);
	void Update(GameState* state, float dt) override;
	bool GetDespawn() { return m_despawn; }
private:
	float m_gravity = 500;
	bool m_despawn = false;
};