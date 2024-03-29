#pragma once

#include <SFML/Graphics.hpp>
#include "ProgramState.h"
#include "Engine.h"

class MainMenuState :
	public ProgramState
{
public:
	MainMenuState(Engine* engine);

	void Init() {}
	void Cleanup() {}

	void HandleEvents(Engine* engine);
	void Update(Engine* engine, float dt);
	void Draw(Engine* engine);

private:

	enum
	{
		START,
		HIGHSCORES,
		QUIT,
		NUM_BUTTONS
	};

	sf::Texture bg_tex;
	sf::Sprite m_background;
	sf::Text m_text[NUM_BUTTONS];
	static const int LINES = 5;
	sf::Text m_controls[LINES];

	sf::Clock floating_clock;
	sf::Sprite m_cloudboy;
	sf::Texture m_tex_cloudboy;
	sf::Vector2f cloud_vel;

	unsigned int m_selected = static_cast<unsigned int>(STATE_GAME);

	sf::Color m_red = sf::Color(244, 66, 66);
	sf::Color m_grey = sf::Color(93, 87, 107);
};

