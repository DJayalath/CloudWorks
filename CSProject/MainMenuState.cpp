#include "MainMenuState.h"
#include "Engine.h"

MainMenuState::MainMenuState(Engine* engine)
{
	sf::Vector2f pos;
	sf::FloatRect text_rect;

	if (!m_font.loadFromFile("./res/fonts/joystix.ttf"))
		std::cout << "ERROR: Failed to load font" << std::endl;

	bg_tex.loadFromFile("./res/MainMenu.png");
	m_background.setTexture(bg_tex);

	// Start Text (DEFAULT)
	m_text[START].setFont(m_font);
	m_text[START].setCharacterSize(36);
	m_text[START].setColor(sf::Color(244, 66, 66));
	m_text[START].setString("START GAME");
	text_rect = m_text[START].getLocalBounds();
	m_text[START].setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos = engine->GetWindow()->getView().getCenter();
	pos.y -= 60;
	m_text[START].setPosition(pos);

	// Quit Text
	m_text[HIGHSCORES].setFont(m_font);
	m_text[HIGHSCORES].setCharacterSize(36);
	m_text[HIGHSCORES].setColor(sf::Color(93, 87, 107));
	m_text[HIGHSCORES].setString("HIGHSCORES");
	text_rect = m_text[HIGHSCORES].getLocalBounds();
	m_text[HIGHSCORES].setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos = engine->GetWindow()->getView().getCenter();
	m_text[HIGHSCORES].setPosition(pos);

	// Quit Text
	m_text[QUIT].setFont(m_font);
	m_text[QUIT].setCharacterSize(36);
	m_text[QUIT].setColor(sf::Color(93, 87, 107));
	m_text[QUIT].setString("QUIT GAME");
	text_rect = m_text[QUIT].getLocalBounds();
	m_text[QUIT].setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos = engine->GetWindow()->getView().getCenter();
	pos.y += 60;
	m_text[QUIT].setPosition(pos);
}

void MainMenuState::HandleEvents(Engine* engine)
{

	if (engine->GetReleased(sf::Keyboard::S) && m_selected < NUM_BUTTONS - 1)
	{
			m_text[m_selected].setColor(m_grey);
			m_text[++m_selected].setColor(m_red);
	}

	if (engine->GetReleased(sf::Keyboard::W) && m_selected > 0)
	{
			m_text[m_selected].setColor(m_grey);
			m_text[--m_selected].setColor(m_red);
	}

	if (engine->GetReleased(sf::Keyboard::Enter))
	{
		switch (m_selected)
		{
		case QUIT:
			engine->GetWindow()->close();
			break;
		case START:
			engine->ChangeState(STATE_GAME);
			break;
		case HIGHSCORES:
			engine->ChangeState(STATE_SCORES);
			break;
		default:
			break;
		}
	}

	if (engine->GetReleased(sf::Keyboard::Escape))
		engine->GetWindow()->close();
}

void MainMenuState::Update(Engine* engine, double dt)
{

}

void MainMenuState::Draw(Engine* engine)
{
	engine->GetWindow()->draw(m_background);
	engine->GetWindow()->draw(m_text[START]);
	engine->GetWindow()->draw(m_text[HIGHSCORES]);
	engine->GetWindow()->draw(m_text[QUIT]);
}
