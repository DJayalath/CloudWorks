#include "EndGameState.h"
#include "Engine.h"
#include <fstream>
#include <sstream>

EndGameState::EndGameState(Engine* engine)
{
	engine->SetLatch(engine->CONTINUE);
	engine->SetLatch(engine->JUMP);
	// Stop any music playing and play the end game sound
	AssetManager::m_music[AssetManager::MAIN].stop();
	AssetManager::m_sounds[AssetManager::LOSE].play();

	// Load background image
	bg_tex.loadFromFile("./res/backgrounds/game_over.png");
	// Set background texture to the background sprite
	m_background.setTexture(bg_tex);
	// Position background in exact centre of screen
	pos = engine->GetWindow()->getView().getCenter();
	// Adjust origin based on dimensions of background texture
	pos.x -= 576 / 2;
	pos.y -= 288 / 2;
	// Set the background sprite's position
	m_background.setPosition(pos);

	// Score text
	m_score.setFont(AssetManager::m_fonts[AssetManager::JOYSTIX]); // Assign font
	m_score.setCharacterSize(36); // Set 36px char size
	m_score.setFillColor(sf::Color(252, 248, 28)); // Fill with 'neon-yellow' colour
	m_score.setString("Score = " + std::to_string((int)engine->GetUserScore()));
	// Centre text horizontally
	text_rect = m_score.getLocalBounds();
	m_score.setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos = engine->GetWindow()->getView().getCenter();
	// Move text just above centre
	pos.y -= 20;
	// Set position attribute in the text variable
	m_score.setPosition(pos);

	// 'Enter Name' text
	m_text.setFont(AssetManager::m_fonts[AssetManager::JOYSTIX]);
	m_text.setCharacterSize(36);
	m_text.setFillColor(sf::Color(93, 87, 107)); // Fill with grey colour
	m_text.setString("Enter Name");
	// Centre text horizontally
	text_rect = m_text.getLocalBounds();
	m_text.setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos = engine->GetWindow()->getView().getCenter();
	// Position vertically
	pos.y += 30;
	m_text.setPosition(pos);

	// Field for displaying player's input
	m_input.setFont(AssetManager::m_fonts[AssetManager::JOYSTIX]);
	m_input.setCharacterSize(36);
	m_input.setFillColor(sf::Color(252, 248, 28)); // Fill in 'neon-yellow' colour
	// Centre horizontally
	text_rect = m_input.getLocalBounds();
	m_input.setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos = engine->GetWindow()->getView().getCenter();
	// Position vertically
	pos.y += 75;
	m_input.setPosition(pos);

	// Read score file to find index to insert score
	std::string line;
	std::ifstream score_file("highscores.data");
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
	if (engine->GetPressed(engine->CONTINUE))
	{
		engine->SetLatch(engine->CONTINUE);
		engine->SetLatch(engine->JUMP);
		// Play sound to indicate submit key pressed to player
		AssetManager::m_sounds[AssetManager::BLIP].play();
		// If no index found, it must be the lowest score so should go to end of file
		if (insertion_index == -1) insertion_index = m_file_buffer.size();
		// Add current round record to vector
		m_file_buffer.insert(m_file_buffer.begin() + 
			insertion_index, engine->GetTextBuffer() + 
			" " + std::to_string((int)engine->GetUserScore()));
		// Re-open highscores file
		std::ofstream out("highscores.data");
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
	else if (engine->GetPressed(engine->BACK))
	{
		engine->SetLatch(engine->BACK);
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