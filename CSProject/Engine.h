#pragma once

#include <SFML/Graphics.hpp>

class Engine
{
public:

	Engine(sf::Uint32 win_width, sf::Uint32 win_height, sf::String win_title);
	void Start();

private:

	sf::RenderWindow m_window;

	sf::Sprite m_sp_background;
	sf::Texture m_tex_background;

	void ProcessInput();
	void Update(float dt);
	void Draw();

};

