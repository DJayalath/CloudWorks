#include "GameState.h"
#include "Engine.h"

#include <iostream>

//IDEA: Moving conveyor belt instead of grass? Randomly generate obstacles rather than terrain?

bool DespawnEnemy(Enemy& e) { return (e.GetHealth() <= 0 || e.GetPosition().y > 800); }
bool DespawnBullet(Bullet& b) { return b.GetDespawn(); }

GameState::GameState() :
	m_player(sf::Vector2f(50, 560), sf::Vector2f(2.0, 2.0), m_assets.texture_map.at("Player"))
{}

void GameState::Init()
{
	// Load background image to texture
	m_tex_background.loadFromFile("./res/BackgroundNew.png");
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
		engine->PushState(STATE_PAUSE);
}
void GameState::Update(Engine* engine, double dt)
{
	if (!m_pause)
	{
		m_dt = dt;

		m_player.SetTerrainHeight(m_terrain_generator.GetHeight(m_player.GetPosition().x, m_player.GetBounds().width, m_chunks.back().GetBounds().width));
		m_player.Update(this, dt);
		m_camera.Update(this);

		for (auto &b : m_bullets)
			b.Update(this, dt);

		for (auto &e : m_enemies)
			e.Update(this, dt);

		m_enemy_manager.Update(this);
		m_terrain_generator.Update(this, m_chunks);

		m_enemies.remove_if(DespawnEnemy);
		m_bullets.remove_if(DespawnBullet);

		if (m_player.GetHealth() == 0 || m_player.GetPosition().y > 720)
		{
			engine->SetUserScore(m_player.GetPosition().x * 0.1 * m_player.GetTime() * m_player.EnemiesKilled() * 100);
			engine->PushState(STATE_ENDGAME);
		}
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

	for (auto &e : m_enemies)
		engine->GetWindow()->draw(e.GetSprite());

	for (auto &p : m_chunks)
		engine->GetWindow()->draw(p.GetSprite());
}

Player* GameState::GetPlayer()
{
	return &m_player;
}