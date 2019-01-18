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
	{}

	void Update(GameState* state, float dt) override
	{}
};

class TerrainGenerator
{
public:
	TerrainGenerator();
	void Update(GameState* state, std::list<Plank>& m_planks);

private:
	float next_spawn = 0;
	float HEIGHT_MIN = 620.f;
	float HEIGHT_MAX = 400.f;
	float HEIGHT_DIFF = 90.f;
	const float SCALE = 0.75f;
	const float PLANK_WIDTH;
	int num_spawned = 0;
};