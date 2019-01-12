#include "EndGameState.h"
#include "Engine.h"
#include <fstream>
#include <sstream>

EndGameState::EndGameState(Engine* engine)
{
	AssetManager::m_music[AssetManager::MAIN].stop();
	AssetManager::m_sounds[AssetManager::LOSE].play();

	if (!m_font.loadFromFile("./res/fonts/joystix.ttf"))
	{
		std::cout << "ERROR: Failed to load font" << std::endl;
	}

	// Background image
	bg_tex.loadFromFile("./res/backgrounds/game_over.png");
	m_background.setTexture(bg_tex);
	// Position background in exact centre of screen
	pos = engine->GetWindow()->getView().getCenter();
	pos.x -= 576 / 2;
	pos.y -= 288 / 2;
	m_background.setPosition(pos);

	// Score text
	m_score.setFont(m_font);
	m_score.setCharacterSize(36);
	m_score.setFillColor(sf::Color(252, 248, 28));
	m_score.setString("Score = " + std::to_string((int)engine->GetUserScore()));
	// Text centering and positioning
	text_rect = m_score.getLocalBounds();
	m_score.setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos = engine->GetWindow()->getView().getCenter();
	pos.y -= 20;
	m_score.setPosition(pos);

	// 'Enter Name' text
	m_text.setFont(m_font);
	m_text.setCharacterSize(36);
	m_text.setFillColor(sf::Color(93, 87, 107));
	m_text.setString("Enter Name");
	text_rect = m_text.getLocalBounds();
	m_text.setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos = engine->GetWindow()->getView().getCenter();
	pos.y += 30;
	m_text.setPosition(pos);

	// Field for displaying player's input
	m_input.setFont(m_font);
	m_input.setCharacterSize(36);
	m_input.setFillColor(sf::Color(252, 248, 28));
	text_rect = m_input.getLocalBounds();
	m_input.setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos = engine->GetWindow()->getView().getCenter();
	pos.y += 75;
	m_input.setPosition(pos);

	// Read score file to find index to insert score
	std::string line;
	std::ifstream score_file("highscores.txt");
	if (score_file.is_open())
	{
		int count = 0; // To track which line we are on
		// Read lines
		while (std::getline(score_file, line))
		{
			// Push current line to vector
			m_file_buffer.push_back(line);

			// Split by space to get name and score (ONLY UNTIL INDEX FOUND)
			if (insertion_index == -1)
			{
				std::stringstream ss(line);
				std::string item;
				unsigned int delim_counter = 0; // Track how many spaces were found
				while (insertion_index == -1 && std::getline(ss, item, ' '))
				{
					// The score will always be on an odd delimiter count
					// and check if the score read is less than the user's score this round
					// If so, this is where the new score should be inserted
					// since the file is sorted from highest score to lowest
					if (delim_counter % 2 != 0 && std::stoi(item) < engine->GetUserScore())
						insertion_index = count;

					delim_counter++;
				}
			}
			count++;
		}
		score_file.close();
	}
	else
		std::cout << "Failed to read highscores file" << std::endl;

	engine->StartTextBuffer();
}

void EndGameState::HandleEvents(Engine* engine)
{
	if (engine->GetReleased(sf::Keyboard::Enter))
	{
		// Play sound to indicate submit key pressed to player
		AssetManager::m_sounds[AssetManager::BLIP].play();
		// If no index found, it must be the lowest score so should go to end of file
		if (insertion_index == -1) insertion_index = m_file_buffer.size();
		// Add current round record to vector
		m_file_buffer.insert(m_file_buffer.begin() + 
			insertion_index, engine->GetTextBuffer() + 
			" " + std::to_string((int)engine->GetUserScore()));
		// Re-open highscores file
		std::ofstream out("highscores.txt");
		// Write each record in buffer back to file
		for (auto &record : m_file_buffer)
			out << record << std::endl;
		// Close file
		out.close();
		// Clear buffer
		m_file_buffer.clear();
		// Close the text buffer
		engine->CloseTextBuffer();
		// Reset the window view
		engine->GetWindow()->setView(engine->GetWindow()->getDefaultView());
		// Switch back into the menu state
		engine->ChangeState(STATE_MAINMENU);
	}
	else if (engine->GetReleased(sf::Keyboard::Escape))
	{
		AssetManager::m_sounds[AssetManager::BLIP].play();
		engine->CloseTextBuffer();
		// Reset view
		engine->GetWindow()->setView(engine->GetWindow()->getDefaultView());
		engine->ChangeState(STATE_MAINMENU);
	}
}

void EndGameState::Update(Engine* engine, float dt)
{
	m_input.setString(engine->GetTextBuffer());

	// Re-centre text as user types
	text_rect = m_input.getLocalBounds();
	m_input.setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos = engine->GetWindow()->getView().getCenter();
	pos.y += 75;
}

void EndGameState::Draw(Engine* engine)
{
	engine->GetWindow()->draw(m_background);
	engine->GetWindow()->draw(m_text);
	engine->GetWindow()->draw(m_input);
	engine->GetWindow()->draw(m_score);
}