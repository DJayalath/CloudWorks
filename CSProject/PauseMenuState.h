#pragma once
#include <SFML/Graphics.hpp>
#include "ProgramState.h"
class PauseMenuState :
	public ProgramState
{
public:
	PauseMenuState(Engine* engine);

	void Init() {}
	void Cleanup() {}

	void HandleEvents(Engine* engine);
	void Update(Engine* engine, double dt);
	void Draw(Engine* engine);

private:

	static const int NUM_BUTTONS = 3;

	enum Button{RESUME, RESTART, MENU};
	unsigned int m_selected = RESUME;

	sf::Texture bg_tex;
	sf::Sprite m_background;

	sf::Vector2f pos;
	sf::FloatRect text_rect;

	sf::Font m_font;
	sf::Text m_text[NUM_BUTTONS];
};

