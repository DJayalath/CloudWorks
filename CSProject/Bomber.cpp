#include "Bomber.h"
#include "GameState.h"
#include "AssetManager.h"

sf::Clock Bomber::m_timer;

Bomber::Bomber(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture) :
	Entity(position, scale, texture)
{
	m_velocity.x = -200;
}

void Bomber::Update(GameState* state, float dt)
{
	m_position += m_velocity * dt;
	m_sprite.setPosition(m_position);

	// Random drop if in range
	if (m_state == DELIVERING && m_position.x < state->GetPlayer()->GetPosition().x + 500 && (int)m_timer.getElapsedTime().asSeconds() % 2 == 0)
	{
		// DROP BOMB
		m_state = STOPPED;
		m_velocity.x = 0;
		m_pause_time = m_timer.getElapsedTime().asMilliseconds();

	}
	else if (m_state == STOPPED && m_timer.getElapsedTime().asMilliseconds() - m_pause_time > 500)
	{
		state->GetBombs().push_back(Bomb(m_position + sf::Vector2f(m_sprite.getGlobalBounds().width,
			m_sprite.getGlobalBounds().height) / 2.f + sf::Vector2f(0, 25),
			sf::Vector2f(0.01f, 0.01f), AssetManager::m_textures[AssetManager::ANVIL]));
		m_state = DROPPED;
	}
	else if (m_state == DROPPED && m_timer.getElapsedTime().asMilliseconds() - m_pause_time > 1000)
	{
		m_velocity.x = -200;
		m_state = LEAVING;
	}

	if (m_position.x < state->GetPlayer()->GetPosition().x - 1280)
		m_despawn = true;
}
