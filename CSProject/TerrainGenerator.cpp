#include "TerrainGenerator.h"
#include "GameState.h"

sf::Texture TerrainGenerator::m_tex;

TerrainGenerator::TerrainGenerator()
{
	m_tex.loadFromFile("./res/wooden_plank.png");
}

void TerrainGenerator::Update(GameState* state, std::list<Plank>& m_planks)
{
	if (state->GetPlayer()->GetPosition().x + 900 > next_spawn)
	{
		if (state->GetPlayer()->GetPosition().x - 900 > m_planks.front().GetPosition().x)
			m_planks.erase(m_planks.begin());

		if (rand() % 2 != 0 || last_empty)
		{
			
			CreateNewTerrain(m_planks);
			last_empty = false;
		}
		else
		{
			empty_space.push_back(next_spawn);
			next_spawn += m_planks.back().GetBounds().width;
			last_empty = true;
		}
	}

	if (!empty_space.empty())
		if (empty_space.front() + 1280 < state->GetPlayer()->GetPosition().x)
			empty_space.erase(empty_space.begin());
}