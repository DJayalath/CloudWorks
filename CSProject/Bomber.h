#pragma once
#include "Entity.h"
class Bomber :
	public Entity
{
public:
	Bomber(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture);
	void Update(GameState* state, double dt) override;
	bool GetDespawn() { return m_despawn; }

private:
	static sf::Clock m_timer;
	bool m_despawn = false;
	enum {DELIVERING, STOPPED, DROPPED, LEAVING};
	int m_state = DELIVERING;
	float m_pause_time = 0;
};