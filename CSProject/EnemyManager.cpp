#include "EnemyManager.h"
#include "GameState.h"


EnemyManager::EnemyManager()
{}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update(GameState* state)
{
	// Get elapsed time between spawns
	spawn_time = spawn_timer.getElapsedTime().asSeconds();

	// Attempt to spawn if time exceeds cooldown
	if (spawn_time > 1)
	{
		// Reset timer
		spawn_timer.restart();

		// Make spawn chance increase as player travels linearly
		m_spawn_chance = state->GetPlayer()->GetPosition().x / max_chance + 0.2;
		// Generate random float between 0 and 1
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		// Spawn enemy if random float is less than the spawn chance
		if (r < m_spawn_chance)
			state->GetEnemies()->push_back(Enemy(sf::Vector2f(state->GetPlayer()->GetPosition().x + 1280,
				state->GetPlayer()->GetTerrainHeight() - 5),
				sf::Vector2f(3.5, 3.5), state->GetAssets()->texture_map.at("Sprite")));

	}
}
