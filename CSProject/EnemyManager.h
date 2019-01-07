#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <cmath>

#include "Enemy.h"

class GameState;
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void Update(GameState* state);
private:

	sf::Clock spawn_timer;
	float spawn_time;
	float m_spawn_chance;
	const float max_chance = 100000.f;
};

