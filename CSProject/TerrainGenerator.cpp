#include "TerrainGenerator.h"
#include "GameState.h"
#include "AssetManager.h"

TerrainGenerator::TerrainGenerator() :
	PLANK_WIDTH(AssetManager::m_textures[AssetManager::PLANK].getSize().x * SCALE)
{}

void TerrainGenerator::Update(GameState* state, std::list<Plank>& m_planks)
{
	// Test if a new 'plank' needs to be generated from camera's position
	// Although the player can only see ahead 640 pixels from the camera
	// centre, 900 pixels are added to allow room for enemies to be spawned
	while (state->GetCamera()->GetCentre().x + 900 > next_spawn)
	{
		// Creates new 'Plank' in the list at constant height and scale but uses the variable
		// 'next_spawn' to determine the horizontal position of the plank.
		m_planks.push_back(Plank(sf::Vector2f(next_spawn, HEIGHT_MIN), sf::Vector2f(0.75f, 0.75f),
			AssetManager::m_textures[AssetManager::PLANK]));
		num_spawned++;
		// 'next_spawn' is incremented by the width of the plank so that the next plank will
		// be spawned exactly next to the current plank
		next_spawn += PLANK_WIDTH;
	}

	// Delete any 'planks' that move behind camera out of view
	while (state->GetCamera()->GetCentre().x - (640 + PLANK_WIDTH) > m_planks.front().GetPosition().x)
		m_planks.erase(m_planks.begin());
}