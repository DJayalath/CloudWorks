#include "Enemy.h"
#include "GameState.h"

Enemy::Enemy(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture) :
	Entity(position, scale, texture)
{
	m_velocity.x = 90;
}

Enemy::~Enemy() {}

void Enemy::Update(GameState* state, double dt)
{
	Move(state->GetPlayer()->GetPosition().x, (float) dt, state);
	BulletCollisions(state->GetBullets(), state);
}

void Enemy::Move(float player_x, float dt, GameState* state)
{
	float direction = -1;

	if (player_x - m_position.x > 0)
		direction = 1;

	jump_time = jump_timer.getElapsedTime().asSeconds();
	if (jump_time > 1 && grounded)
	{
		grounded = false;
		jump_timer.restart();
		Jump(dt);
	}

	if (!grounded)
	{
		m_velocity.y += 500 * dt;

		if (m_position.y > state->GetHeight(m_position.x, this->GetBounds().width) - 5)
		{
			if (m_position.y < 800)
			{
				m_position.y = state->GetHeight(m_position.x, this->GetBounds().width) - 5;
				m_velocity.y = 0;
				grounded = true;
			}
		}
	}

	m_position.y += m_velocity.y * dt;
	m_position.x += m_velocity.x * direction * dt;

	m_sprite.setPosition(m_position);
}

void Enemy::Jump(float dt)
{
	m_velocity.y -= 350;
}

void Enemy::BulletCollisions(std::list<Bullet>* bullets, GameState* state)
{
	for (auto &&b : *bullets)
	{
		if (this->GetBounds().intersects(b.GetBounds()))
		{
			m_health = 0;
			b.SetDespawn(true);
			state->GetPlayer()->EnemiesKilled() += 1;
		}
	}
}