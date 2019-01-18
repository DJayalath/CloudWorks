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
	// Apply velocity to position
	m_position += m_velocity * dt;
	// Update sprite position
	m_sprite.setPosition(m_position);

	switch (m_state)
	{
	case DELIVERING:
		// Test if within 500 pixels of player and on an even second
		if (m_position.x < state->GetPlayer()->GetPosition().x + 500 &&
			(int)m_timer.getElapsedTime().asSeconds() % 2 == 0)
		{
			// Halt the bomber
			m_velocity.x = 0;
			// Start timing how long the bomber is halted
			m_pause_time = m_timer.getElapsedTime().asMilliseconds();
			// Switch to 'STOPPED' state
			m_state = STOPPED;
		}
		break;
	case STOPPED:
		// Test if the time halted is greater than 500ms
		if (m_timer.getElapsedTime().asMilliseconds() - m_pause_time > 500)
		{
			// Drop a bomb from the height of the bomber with a small adjustment
			// to ensure bomb starts from slightly below the bomber's base
			state->GetBombs().push_back(Bomb(m_position + sf::Vector2f(m_sprite.getGlobalBounds().width,
				m_sprite.getGlobalBounds().height) / 2.f + sf::Vector2f(0, 25),
				sf::Vector2f(0.01f, 0.01f), AssetManager::m_textures[AssetManager::ANVIL]));
			// Switch to the 'DROPPED' state
			m_state = DROPPED;
		}
		break;
	case DROPPED:
		// Test if the time elapsed since dropping the bomb exceeds 500ms
		if (m_timer.getElapsedTime().asMilliseconds() - m_pause_time > 1000)
		{
			// Start the bomber moving again
			m_velocity.x = -200;
			// Switch to 'LEAVING' state
			m_state = LEAVING;
		}
		break;
	case LEAVING:
		// Test if the bomber has now gone behind the view and
		// set to despawn on next frame.
		if (m_position.x < state->GetCamera()->GetCentre().x - 1280)
			m_despawn = true;
		break;
	default:
		break;
	}
}
