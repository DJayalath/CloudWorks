#include "PauseMenuState.h"
#include "Engine.h"

PauseMenuState::PauseMenuState(Engine* engine)
{
	if (!m_font.loadFromFile("./res/fonts/joystix.ttf"))
		std::cout << "ERROR: Failed to load font" << std::endl;

	// Background Texture
	bg_tex.loadFromFile("./res/backgrounds/pause.png");
	m_background.setTexture(bg_tex);
	pos = engine->GetWindow()->getView().getCenter();
	pos.x -= 576 / 2;
	pos.y -= 288 / 2;
	m_background.setPosition(pos);

	// DEFAULT
	m_text[RESUME].setFont(m_font);
	m_text[RESUME].setCharacterSize(36);
	m_text[RESUME].setColor(sf::Color(244, 66, 66));
	m_text[RESUME].setString("RESUME");
	text_rect = m_text[RESUME].getLocalBounds();
	m_text[RESUME].setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos = engine->GetWindow()->getView().getCenter();
	pos.y -= 20;
	m_text[RESUME].setPosition(pos);

	m_text[RESTART].setFont(m_font);
	m_text[RESTART].setCharacterSize(36);
	m_text[RESTART].setColor(sf::Color(93, 87, 107));
	m_text[RESTART].setString("RESTART");
	text_rect = m_text[RESTART].getLocalBounds();
	m_text[RESTART].setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos.y += 50;
	m_text[RESTART].setPosition(pos);

	m_text[MENU].setFont(m_font);
	m_text[MENU].setCharacterSize(36);
	m_text[MENU].setColor(sf::Color(93, 87, 107));
	m_text[MENU].setString("MENU");
	text_rect = m_text[MENU].getLocalBounds();
	m_text[MENU].setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos.y += 50;
	m_text[MENU].setPosition(pos);
}

void PauseMenuState::HandleEvents(Engine* engine)
{
	if (engine->GetReleased(sf::Keyboard::W) && m_selected > 0)
	{
		m_text[m_selected].setColor(sf::Color(93, 87, 107));
		m_text[--m_selected].setColor(sf::Color(244, 66, 66));
	}
	else if (engine->GetReleased(sf::Keyboard::S) && m_selected < NUM_BUTTONS - 1)
	{
		m_text[m_selected].setColor(sf::Color(93, 87, 107));
		m_text[++m_selected].setColor(sf::Color(244, 66, 66));
	}
	else if (engine->GetReleased(sf::Keyboard::Enter))
	{
		switch (m_selected)
		{
		case RESUME:
			engine->PopState();
			break;
		case RESTART:
			engine->GetWindow()->setView(engine->GetWindow()->getDefaultView());
			engine->ChangeState(STATE_GAME);
			break;
		case MENU:
			engine->GetWindow()->setView(engine->GetWindow()->getDefaultView());
			engine->ChangeState(STATE_MAINMENU);
			break;
		default:
			break;
		}
	}
	else if (engine->GetReleased(sf::Keyboard::Escape))
		engine->PopState();
}

void PauseMenuState::Update(Engine* engine, double dt)
{

}

void PauseMenuState::Draw(Engine* engine)
{
	engine->GetWindow()->draw(m_background);
	for (sf::Text& t : m_text)
		engine->GetWindow()->draw(t);
}