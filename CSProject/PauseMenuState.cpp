#include "PauseMenuState.h"
#include "AssetManager.h"
#include "Engine.h"

PauseMenuState::PauseMenuState(Engine* engine)
{

	AssetManager::m_sounds[AssetManager::BLIP].play();
	AssetManager::m_music[AssetManager::MAIN].pause();

	// Background Texture
	bg_tex.loadFromFile("./res/backgrounds/pause.png");
	m_background.setTexture(bg_tex);
	pos = engine->GetWindow()->getView().getCenter();
	pos.x -= 576 / 2;
	pos.y -= 288 / 2;
	m_background.setPosition(pos);

	// DEFAULT
	m_text[RESUME].setFont(AssetManager::m_fonts[AssetManager::JOYSTIX]);
	m_text[RESUME].setCharacterSize(36);
	m_text[RESUME].setFillColor(sf::Color(244, 66, 66));
	m_text[RESUME].setString("RESUME");
	text_rect = m_text[RESUME].getLocalBounds();
	m_text[RESUME].setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos = engine->GetWindow()->getView().getCenter();
	pos.y -= 20;
	m_text[RESUME].setPosition(pos);

	m_text[RESTART].setFont(AssetManager::m_fonts[AssetManager::JOYSTIX]);
	m_text[RESTART].setCharacterSize(36);
	m_text[RESTART].setFillColor(sf::Color(93, 87, 107));
	m_text[RESTART].setString("RESTART");
	text_rect = m_text[RESTART].getLocalBounds();
	m_text[RESTART].setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos.y += 50;
	m_text[RESTART].setPosition(pos);

	m_text[MENU].setFont(AssetManager::m_fonts[AssetManager::JOYSTIX]);
	m_text[MENU].setCharacterSize(36);
	m_text[MENU].setFillColor(sf::Color(93, 87, 107));
	m_text[MENU].setString("MENU");
	text_rect = m_text[MENU].getLocalBounds();
	m_text[MENU].setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	pos.y += 50;
	m_text[MENU].setPosition(pos);
}

void PauseMenuState::HandleEvents(Engine* engine)
{
	if (engine->GetPressed(engine->UP) && m_selected > 0)
	{
		engine->SetLatch(engine->UP);
		AssetManager::m_sounds[AssetManager::SWITCH].play();
		m_text[m_selected].setFillColor(sf::Color(93, 87, 107));
		m_text[--m_selected].setFillColor(sf::Color(244, 66, 66));
	}
	else if (engine->GetPressed(engine->DOWN) && m_selected < NUM_BUTTONS - 1)
	{
		engine->SetLatch(engine->DOWN);
		AssetManager::m_sounds[AssetManager::SWITCH].play();
		m_text[m_selected].setFillColor(sf::Color(93, 87, 107));
		m_text[++m_selected].setFillColor(sf::Color(244, 66, 66));
	}
	else if (engine->GetPressed(engine->CONTINUE))
	{
		engine->SetLatch(engine->CONTINUE);
		engine->SetLatch(engine->JUMP);
		AssetManager::m_sounds[AssetManager::BLIP].play();
		switch (m_selected)
		{
		case RESUME:
			AssetManager::m_music[AssetManager::MAIN].play();
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
	else if (engine->GetPressed(engine->BACK))
	{
		engine->SetLatch(engine->BACK);
		AssetManager::m_sounds[AssetManager::BLIP].play();
		AssetManager::m_music[AssetManager::MAIN].play();
		engine->PopState();
	}
}

void PauseMenuState::Update(Engine* engine, float dt)
{

}

void PauseMenuState::Draw(Engine* engine)
{
	engine->GetWindow()->draw(m_background);
	for (sf::Text& t : m_text)
		engine->GetWindow()->draw(t);
}