#include "TerrainGenerator.h"
#include "GameState.h"

sf::Texture TerrainGenerator::m_tex;

TerrainGenerator::TerrainGenerator()
{
	m_tex.loadFromFile("./res/textures/wooden_plank.png");
}

void TerrainGenerator::Update(GameState* state, std::list<Plank>& m_planks)
{
	if (state->GetCamera()->GetCentre().x + 900 > next_spawn)
	{
		if (state->GetCamera()->GetCentre().x - 900 > m_planks.front().GetPosition().x)
			m_planks.erase(m_planks.begin());

		CreateNewTerrain(m_planks);
	}

	for (auto& plank : m_planks)
	{	
		sf::FloatRect result;
		if (state->GetPlayer()->GetSprite().getGlobalBounds().intersects(plank.GetSprite().getGlobalBounds(), result))
		{
			if (state->GetPlayer()->GetSprite().getPosition().y + state->GetPlayer()->GetSprite().getGlobalBounds().height / 2.f < plank.GetSprite().getPosition().y - plank.GetSprite().getGlobalBounds().height)
			{
				state->GetPlayer()->SetPosition(state->GetPlayer()->GetPosition().x, state->GetPlayer()->GetPosition().y - result.height);
				state->GetPlayer()->SetVelocity(state->GetPlayer()->GetVelocity().x, 0.f);
				if (!state->GetPlayer()->Grounded())
				{
					state->GetPlayer()->Grounded() = true;
				}
			}
			else
				state->GetPlayer()->SetVelocity(0.f, state->GetPlayer()->GetVelocity().y);
		}
	}
}