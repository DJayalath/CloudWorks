#include "Engine.h"

Engine::Engine(sf::Uint32 win_width, sf::Uint32 win_height, sf::String win_title)
{
	// Create window from width, height and title parameters
	m_window.create(sf::VideoMode(win_width, win_height), win_title, sf::Style::Default);

	// Load background image to texture
	m_tex_background.loadFromFile("./res/background.jpg");

	// Assign texture to background sprite
	m_sp_background.setTexture(m_tex_background);
}

void Engine::Start()
{
	sf::Clock clock;
	float dt;

	// Start the game loop
	while (m_window.isOpen())
	{
		// Get time elapsed between frames
		dt = clock.restart().asSeconds();

		ProcessInput();
		Update(dt);
		Draw();
	}
}

void Engine::ProcessInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		m_window.close();
}

void Engine::Update(float dt)
{

}

void Engine::Draw()
{
	// Clear previous buffer
	m_window.clear(sf::Color::White);

	// Draw to buffer
	m_window.draw(m_sp_background);

	// Swap buffers
	m_window.display();
}