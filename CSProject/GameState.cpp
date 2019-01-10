#include "GameState.h"
#include "Engine.h"

#include <iostream>

//IDEA: Moving conveyor belt instead of grass? Randomly generate obstacles rather than terrain?
bool DespawnBullet(Bullet& b) { return b.GetDespawn(); }
bool DespawnBomber(Bomber& b) { return b.GetDespawn(); }
bool DespawnBomb(Bomb& b) { return b.GetDespawn(); }

GameState::GameState() :
	m_player(sf::Vector2f(400, 400), sf::Vector2f(3.f, 3.f), m_assets.texture_map.at("Player"))
{
}

void GameState::Init()
{
	// Load background image to texture
	m_tex_background.loadFromFile("./res/backgrounds/game.png");
	// Enable anti-aliasing to smooth texture
	m_tex_background.setSmooth(true);
	// Ensure texture repeats so it can be infinite
	m_tex_background.setRepeated(true);

	// Assign texture variable to background sprite
	m_sp_background.setTexture(m_tex_background);
	// Set texture size (temporarily set very wide) for scrolling
	m_sp_background.setTextureRect(sf::IntRect(0, 0, 128000, 720));

	// Generate 16 initial chunks...
	for (int i = 0; i < 16; i++)
		m_terrain_generator.CreateNewTerrain(m_chunks);
}

void GameState::Cleanup() {}
void GameState::Pause()
{
	m_pause = true;
}
void GameState::Resume()
{
	m_pause = false;
}

void GameState::HandleEvents(Engine* engine)
{
	if (engine->GetReleased(sf::Keyboard::Escape))
	{
		m_assets.sound_map.at("Blip").play();
		engine->PushState(STATE_PAUSE);
	}
}
void GameState::Update(Engine* engine, double dt)
{
	m_player.Update(this, dt);
	m_camera.Update(this, dt);

	sf::FloatRect result;
	for (auto &b : m_bullets)
	{
		// Ground collision tests
		for (auto &c : m_chunks)
			if (b.GetSprite().getGlobalBounds().intersects(c.GetSprite().getGlobalBounds(), result))
				b.GroundCollision(result.height);

		// Bomber collision and removal tests
		m_bombers.erase(std::remove_if(m_bombers.begin(), m_bombers.end(),
			[&](Bomber& s) 
		{
			if (b.GetSprite().getGlobalBounds().intersects(s.GetSprite().getGlobalBounds()))
			{
				m_player.EnemiesKilled() += 1;
				return true;
			}
			return false;
		}), m_bombers.end());

		b.Update(this, dt);
	}

	for (auto &b : m_bombers)
		b.Update(this, dt);

	for (auto &b : m_bombs)
	{
		// Chunk collisions and removal
		m_chunks.erase(std::remove_if(m_chunks.begin(), m_chunks.end(),
			[&](Plank& p)
		{ 
			if (b.GetSprite().getGlobalBounds().intersects(p.GetSprite().getGlobalBounds()))
			{
				m_assets.sound_map.at("Hit").play();
				return true;
			}
		}), m_chunks.end());

		// Player colision
		if (b.GetSprite().getGlobalBounds().intersects(m_player.GetSprite().getGlobalBounds()))
			m_player.SetHealth(0);

		b.Update(this, dt);
	}

	for (auto &s : m_spikes)
	{
		// Player collision
		if (s.GetSprite().getGlobalBounds().intersects(m_player.GetSprite().getGlobalBounds()))
			m_player.SetHealth(0);

		// Ground collision
		for (auto &c : m_chunks)
			if (s.GetSprite().getGlobalBounds().intersects(c.GetSprite().getGlobalBounds(), result))
			{
				// Test if collision is NOT side on
				if (s.GetSprite().getPosition().y + s.GetSprite().getGlobalBounds().height / 2.f < c.GetSprite().getPosition().y - c.GetSprite().getGlobalBounds().height)
					s.GroundCollision(result.height);
				else
					s.SetVelocity(0, s.GetVelocity().y);
			}

		s.Update(this, dt);
	}

	// Generate new floor tiles as player travels
	m_terrain_generator.Update(this, m_chunks);
	
	// Generate bombers/spikes in timed intervals
	if ((int) m_timer.getElapsedTime().asMilliseconds() > 500)
	{
		m_timer.restart();
		if (rand() % 9 == 0)
		{
			bool valid_spawn = true;
			for (auto &b : m_bombers)
				if (b.GetPosition().x > m_camera.GetCentre().x + 400)
				{
					valid_spawn = false;
					break;
				}
			if (valid_spawn)
				m_bombers.push_back(Bomber(m_camera.GetCentre() + sf::Vector2f(800, -200), sf::Vector2f(0.3f, 0.3f), m_assets.texture_map.at("Bomber")));
		}
		if (rand() % 5 == 0)
		{
			bool valid_spawn = true;
			for (auto &s : m_spikes)
				if (s.GetPosition().x > m_camera.GetCentre().x + 400)
				{
					valid_spawn = false;
					break;
				}
			if (valid_spawn)
				m_spikes.push_back(Spike(sf::Vector2f(m_camera.GetCentre().x + 800, 550), sf::Vector2f(2.5f, 2.5f), m_assets.texture_map.at("Spike")));
		}
	}

	m_bullets.remove_if(DespawnBullet);
	std::remove_if(m_bombers.begin(), m_bombers.end(), DespawnBomber);
	std::remove_if(m_bombs.begin(), m_bombs.end(), DespawnBomb);
	std::remove_if(m_spikes.begin(), m_spikes.end(), [=](Spike& s) 
		{return s.GetPosition().x < m_player.GetPosition().x - 1280 || s.GetPosition().y > 900; });

	if (m_player.GetHealth() == 0 || m_player.GetPosition().y > 720)
	{
		engine->SetUserScore(m_player.GetPosition().x * 0.1 + 10 * m_player.GetTime() + 100 * m_player.EnemiesKilled());
		m_assets.sound_map.at("Lose").play();
		engine->PushState(STATE_ENDGAME);
	}
}
void GameState::Draw(Engine* engine)
{
	engine->GetWindow()->setView(m_camera.GetView());
	engine->GetWindow()->draw(m_sp_background);
	engine->GetWindow()->draw(m_player.GetSprite());

	// On Screen Text
	engine->GetWindow()->draw(m_camera.GetDistText());
	engine->GetWindow()->draw(m_camera.GetHealthText());
	engine->GetWindow()->draw(m_camera.GetTimeText());

	for (auto &b : m_bullets)
		engine->GetWindow()->draw(b.GetSprite());

	for (auto &b : m_bombers)
		engine->GetWindow()->draw(b.GetSprite());

	for (auto &b : m_bombs)
		engine->GetWindow()->draw(b.GetSprite());

	for (auto &s : m_spikes)
		engine->GetWindow()->draw(s.GetSprite());

	for (auto &p : m_chunks)
		engine->GetWindow()->draw(p.GetSprite());
}

Player* GameState::GetPlayer()
{
	return &m_player;
}