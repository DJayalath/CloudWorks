#pragma once

#include <SFML/Graphics.hpp>

#include "ProgramState.h"

class EndGameState :
	public ProgramState
{
public:
	EndGameState(Engine* engine);

	void Init() {}
	void Cleanup() {}

	void HandleEvents(Engine* engine);
	void Update(Engine* engine, float dt);
	void Draw(Engine* engine);

private:

	sf::Texture bg_tex;
	sf::Sprite m_background;

	sf::Vector2f pos;
	sf::FloatRect text_rect;

	sf::Font m_font;
	sf::Text m_score;
	sf::Text m_text;
	sf::Text m_input;

	std::vector<std::string> m_file_buffer;
	int insertion_index = -1;
};

