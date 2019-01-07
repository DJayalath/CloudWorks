#pragma once

#include <SFML/Graphics.hpp>
#include "ProgramState.h"

class ScoresState :
	public ProgramState
{
public:
	ScoresState(Engine* engine);

	void Init() {}
	void Cleanup() {}

	void HandleEvents(Engine* engine);
	void Update(Engine* engine, double dt);
	void Draw(Engine* engine);

private:
	static const int NUM_SCORES = 10;
	sf::Texture bg_tex;
	sf::Sprite m_background;
	sf::Vector2f pos;
	sf::FloatRect text_rect;
	sf::Font m_font;
	std::vector<std::string> score_buffer[NUM_SCORES];
	sf::Text m_names[NUM_SCORES];
	sf::Text m_scores[NUM_SCORES];
	sf::Text m_place[NUM_SCORES];
	int count = 0;
};

