#include "GameState.h"
#include "Engine.h"

#include <iostream>

GameState::GameState() :
	m_player(sf::Vector2f(400, 400), sf::Vector2f(3.f, 3.f),
		AssetManager::m_textures[AssetManager::PLAYER])
{}

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

	// PLAY THE MUSIC!
	AssetManager::m_music[AssetManager::MAIN].play();
}

void GameState::Cleanup() {}
void GameState::Pause()
{
}
void GameState::Resume()
{
}

void GameState::HandleEvents(Engine* engine)
{
	// Check if escape pressed
	if (engine->GetPressed(engine->BACK))
	{
		engine->SetLatch(engine->BACK);
		// Push pause menu to vector
		engine->PushState(STATE_PAUSE);
	}
}
void GameState::Update(Engine* engine, float dt)
{
	// Move player based on game inputs
	if (engine->GetPressed(engine->LEFT))
		m_player.Accelerate(-1, dt);
	else if (engine->GetPressed(engine->RIGHT))
		m_player.Accelerate(1, dt);
	else
		m_player.ApplyFriction(dt);

	if (engine->GetPressed(engine->JUMP))
		m_player.Jump(dt);

	m_player.Update(this, dt);


	m_camera.Update(this, dt);

	sf::FloatRect result;

	for (auto &b : m_bombers)
		b.Update(this, dt);

	// Loop through all bombs checking for collisions
	for (auto &b : m_bombs)
	{
		// Chunk collisions and removal
		m_chunks.erase(std::remove_if(m_chunks.begin(), m_chunks.end(),
			[&](Plank& p)
			{
				// If this bomb collides with a plank, erase it!
				if (b.GetSprite().getGlobalBounds().intersects(p.GetSprite().getGlobalBounds()))
				{
					// Play a sound to indicate a plank has been destroyed
					AssetManager::m_sounds[AssetManager::HIT].play();
					return true;
				}
				// Otherwise, don't erase it!
				return false;
			}), m_chunks.end());

		// If the player collides with this bomb, set health to zero (player dies)
		if (b.GetSprite().getGlobalBounds().intersects(m_player.GetSprite().getGlobalBounds()))
			m_player.SetHealth(0);

		// Update bomb position
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
				{
					s.GetPosition().y -= result.height;
					s.GetVelocity().y = 0;
				}
				else
					s.SetVelocity(0, s.GetVelocity().y);
			}

		s.Update(this, dt);
	}

	// Testing for player collisions with 'planks'
	for (auto &c : m_chunks)
	{
		// Check if an intersection has occured and if so, load the intersection bounds into the
		// SFML rectangle 'result'
		if (m_player.GetSprite().getGlobalBounds().intersects(c.GetSprite().getGlobalBounds(), result))
		{
			// Check if the player has impacted a 'plank' vertically rather than 'side-on' by checking
			// if the user's 'feet' height is higher than the top of the 'plank'
			if (m_player.GetSprite().getPosition().y + m_player.GetSprite().getGlobalBounds().height <
				c.GetSprite().getPosition().y + c.GetSprite().getGlobalBounds().height)
			{
				// In a vertical collision, the player's height must be reset using the intersection height
				// and the player's vertical velocity must be zero when they hit a solid object
				m_player.SetPosition(m_player.GetPosition().x, m_player.GetPosition().y - result.height);
				m_player.SetVelocity(m_player.GetVelocity().x, 0.f);
				// The player is now grounded
				if (!m_player.Grounded())
					m_player.Grounded() = true;
			}
			else
			{
				// In the case of a side-on collision, the user's horizontal velocity must be set to zero
				// The user may not have hit ground yet so their grounded status doesn't change
				m_player.SetVelocity(0.f, m_player.GetVelocity().y);
				m_player.Grounded() = false;
			}
		}
	}

	// Generate new floor tiles as player travels
	m_terrain_generator.Update(this, m_chunks);

	// Generate bombers/spikes in timed intervals
	if ((int)m_timer.getElapsedTime().asMilliseconds() > 500)
	{
		// Restart timer after 500ms
		m_timer.restart();
		// Set difiiculty based on distance camera has travelled
		int difficulty = std::min((int)m_camera.GetCentre().x / 5000, 4);
		// If random number equals zero then try and spawn bomber
		if (rand() % (9 - difficulty) == 0)
		{
			// Assume a valid spawn
			bool valid_spawn = true;
			// Test for near entities by looping through other bombers
			for (auto &b : m_bombers)
				if (b.GetPosition().x > m_camera.GetCentre().x + 400)
				{
					// If another bomber is within 400 pixels, set flag to false
					valid_spawn = false;
					break;
				}
			// Only spawn if valid
			if (valid_spawn)
				m_bombers.push_back(Bomber(m_camera.GetCentre() + sf::Vector2f(800, -200), sf::Vector2f(0.3f, 0.3f),
					AssetManager::m_textures[AssetManager::BOMBER]));
		}
		if (rand() % (5 - difficulty) == 0)
		{
			// Assume a valid spawn
			bool valid_spawn = true;
			// Loop through other 'Spikes' for near entities
			for (auto &s : m_spikes)
				if (s.GetPosition().x > m_camera.GetCentre().x + 400)
				{
					// Set to false if within 400 pixels of another 'Spike'
					valid_spawn = false;
					break;
				}
			// Only spawn new 'Spike' if valid (not near another 'Spike')
			if (valid_spawn)
				m_spikes.push_back(Spike(sf::Vector2f(m_camera.GetCentre().x + 800, 550), sf::Vector2f(2.5f, 2.5f),
					AssetManager::m_textures[AssetManager::SPIKE]));
		}
	}

	// Erase flagged bombers
	m_bombers.erase(std::remove_if(m_bombers.begin(), m_bombers.end(),
		[&](Bomber& b) {return b.GetDespawn(); }), m_bombers.end());
	// Erase flagged bombs
	m_bombs.erase(std::remove_if(m_bombs.begin(), m_bombs.end(),
		[&](Bomb& b) {return b.GetDespawn(); }), m_bombs.end());
	// Erase flagged spikes
	m_spikes.erase(std::remove_if(m_spikes.begin(), m_spikes.end(),
		[&](Spike& s) {return s.GetDespawn(); }), m_spikes.end());

	// If player dies or falls off the screen, go to 'game over' screen
	if (m_player.GetHealth() == 0 || m_player.GetPosition().y > 720)
	{
		// Set the final weighted user score
		engine->SetUserScore(m_player.GetPosition().x * 0.1f + 50.f * m_player.GetTime());
		// Push the end game state to the state vector
		engine->PushState(STATE_ENDGAME);
	}
}
void GameState::Draw(Engine* engine)
{
	engine->GetWindow()->setView(m_camera.GetView());
	// Draw background sprite
	engine->GetWindow()->draw(m_sp_background);
	engine->GetWindow()->draw(m_player.GetSprite());

	// On Screen Text
	engine->GetWindow()->draw(m_camera.GetDistText());
	engine->GetWindow()->draw(m_camera.GetHealthText());
	engine->GetWindow()->draw(m_camera.GetTimeText());

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