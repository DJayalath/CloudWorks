#include "ScoresState.h"
#include "Engine.h"
#include <fstream>
#include <sstream>

ScoresState::ScoresState(Engine* engine)
{
	if (!m_font.loadFromFile("./res/fonts/joystix.ttf"))
	{
		std::cout << "ERROR: Failed to load font" << std::endl;
	}

	bg_tex.loadFromFile("./res/backgrounds/high_scores.png");
	m_background.setTexture(bg_tex);

	sf::Vector2f pos = engine->GetWindow()->getView().getCenter();

	// Read score file
	std::string line;
	std::ifstream score_file("highscores.txt");
	if (score_file.is_open())
	{
		// Read lines from file
		while (std::getline(score_file, line) && count < NUM_SCORES)
		{
			// Split by space to get name and score
			std::stringstream ss(line);
			std::string item;

			// Push delimited items onto vector
			while (std::getline(ss, item, ' '))
				score_buffer[count].push_back(item);

			count++;
		}
		score_file.close();
	}
	else
		std::cout << "Failed to read highscores file" << std::endl;

	pos.x -= 265;
	pos.y -= 60;
	for (int i = 0; i < count; i++)
	{
		// Load names and scores into text fields
		m_names[i].setString(score_buffer[i].at(0));
		m_scores[i].setString(score_buffer[i].at(1));
		m_place[i].setString(std::to_string(i + 1));

		// Set fonts
		m_names[i].setFont(m_font);
		m_scores[i].setFont(m_font);
		m_place[i].setFont(m_font);

		// Set sizes
		m_names[i].setCharacterSize(24);
		m_scores[i].setCharacterSize(24);
		m_place[i].setCharacterSize(24);

		// Set positions
		m_names[i].setPosition(pos);
		m_scores[i].setPosition(pos + sf::Vector2f(340, 0));
		m_place[i].setPosition(pos + sf::Vector2f(-60, 0));
		pos.y += 25;
	}
}

void ScoresState::HandleEvents(Engine* engine)
{
	if (engine->GetReleased(sf::Keyboard::Escape))
	{
		AssetManager::m_sounds[AssetManager::BLIP].play();
		engine->ChangeState(STATE_MAINMENU);
	}
}

void ScoresState::Update(Engine* engine, double dt)
{
}

void ScoresState::Draw(Engine* engine)
{
	engine->GetWindow()->draw(m_background);
	for (int i = 0; i < count; i++)
	{
		engine->GetWindow()->draw(m_names[i]);
		engine->GetWindow()->draw(m_scores[i]);
		engine->GetWindow()->draw(m_place[i]);
	}
}
