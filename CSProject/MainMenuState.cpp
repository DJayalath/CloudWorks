#include "MainMenuState.h"
#include "Engine.h"
#include "Maths.h"

MainMenuState::MainMenuState(Engine* engine)
{
	floating_clock.restart();

	m_tex_cloudboy.loadFromFile("./res/textures/player.png");
	m_cloudboy.setTexture(m_tex_cloudboy);
	m_cloudboy.setScale(9.f, 9.f);
	m_cloudboy.setPosition(engine->GetWindow()->getView().getCenter() + sf::Vector2f(300,-120));

	sf::Vector2f pos;
	sf::FloatRect text_rect;

	if (!m_font.loadFromFile("./res/fonts/joystix.ttf"))
		std::cout << "ERROR: Failed to load font" << std::endl;

	bg_tex.loadFromFile("./res/backgrounds/main_menu.png");
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

	// Controls Text
	for (auto &t : m_controls)
	{
		t.setFont(m_font);
		t.setCharacterSize(18);
		t.setColor(sf::Color::White);
	}
	// Controls Title
	m_controls[0].setString("Controls");
	m_controls[0].setColor(sf::Color::Yellow);
	m_controls[0].setCharacterSize(24);
	text_rect = m_controls[0].getLocalBounds();
	m_controls[0].setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	m_controls[0].setPosition(engine->GetWindow()->getView().getCenter() + sf::Vector2f(-400, -58));
	// Line 1
	m_controls[1].setString("W/S = Menu Up/Down");
	text_rect = m_controls[1].getLocalBounds();
	m_controls[1].setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	m_controls[1].setPosition(engine->GetWindow()->getView().getCenter() + sf::Vector2f(-400, -28));
	// Line 2
	m_controls[2].setString("Enter = Continue");
	text_rect = m_controls[2].getLocalBounds();
	m_controls[2].setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	m_controls[2].setPosition(engine->GetWindow()->getView().getCenter() + sf::Vector2f(-400, 2));
	// Line 3
	m_controls[3].setString("Escape = Pause/Return");
	text_rect = m_controls[3].getLocalBounds();
	m_controls[3].setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	m_controls[3].setPosition(engine->GetWindow()->getView().getCenter() + sf::Vector2f(-400, 32));
	// Line 4
	m_controls[4].setString("W/A/S = Jump/Left/Right");
	text_rect = m_controls[4].getLocalBounds();
	m_controls[4].setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
	m_controls[4].setPosition(engine->GetWindow()->getView().getCenter() + sf::Vector2f(-400, 62));
}

void MainMenuState::HandleEvents(Engine* engine)
{

	if (engine->GetReleased(sf::Keyboard::S) && m_selected < NUM_BUTTONS - 1)
	{
		AssetManager::m_sounds[AssetManager::SWITCH].play();
		m_text[m_selected].setColor(m_grey);
		m_text[++m_selected].setColor(m_red);
	}

	if (engine->GetReleased(sf::Keyboard::W) && m_selected > 0)
	{
		AssetManager::m_sounds[AssetManager::SWITCH].play();
		m_text[m_selected].setColor(m_grey);
		m_text[--m_selected].setColor(m_red);
	}

	if (engine->GetReleased(sf::Keyboard::Enter))
	{
		AssetManager::m_sounds[AssetManager::BLIP].play();
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
	cloud_vel.y = sinf(Maths::GetRadians(floating_clock.getElapsedTime().asMilliseconds() / 5.f)) * 50;
	cloud_vel.x = cosf(Maths::GetRadians(floating_clock.getElapsedTime().asMilliseconds() / 10.f)) * 20;
	m_cloudboy.move(cloud_vel * static_cast<float>(dt));
}

void MainMenuState::Draw(Engine* engine)
{
	engine->GetWindow()->draw(m_background);
	engine->GetWindow()->draw(m_text[START]);
	engine->GetWindow()->draw(m_text[HIGHSCORES]);
	engine->GetWindow()->draw(m_text[QUIT]);

	for (auto &t : m_controls)
		engine->GetWindow()->draw(t);

	engine->GetWindow()->draw(m_cloudboy);
}
