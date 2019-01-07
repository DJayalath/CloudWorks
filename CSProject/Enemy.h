#pragma once

#include "Entity.h"
#include "Bullet.h"
#include <list>

class Enemy : public Entity
{
public:
	Enemy(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture);
	~Enemy();

	void Update(GameState* state, double dt) override;

private:

	sf::Clock jump_timer;
	float jump_time;
	bool grounded = true;

	void Move(float player_x, float dt, GameState* state);
	void Jump(float dt);
	void BulletCollisions(std::list<Bullet>* bullets, GameState* state);
};