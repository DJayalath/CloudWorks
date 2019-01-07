#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Entity.h"

class Plank : public Entity
{
public:
	Plank(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture) : 
		Entity(position, scale, texture)
	{
	}

	void Update(GameState* state, double dt) override
	{

	}

	float& Height() { return m_height; }
private:
	float m_height = 560;
};

class TerrainGenerator
{
public:
	TerrainGenerator();

	void CreateNewTerrain(std::list<Plank>& m_planks)
	{
		m_planks.push_back(Plank(sf::Vector2f(next_spawn, 620), sf::Vector2f(0.75f, 0.75f), m_tex));
		next_spawn += m_planks.back().GetBounds().width;
	}

	void Update(GameState* state, std::list<Plank>& m_planks);
	float GetHeight(int x, int object_width, int width)
	{
		for (auto& i : empty_space)
		{
			if (x >= i && x + object_width <= i + width)
				return 900;
		}

		return 560;
	}

private:
	static sf::Texture m_tex;
	float next_spawn = 0;
	std::vector<float> empty_space;
	bool last_empty = false;
};