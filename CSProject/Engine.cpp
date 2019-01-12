#include "Engine.h"
#include "GameState.h"
#include "EndGameState.h"
#include "MainMenuState.h"
#include "ScoresState.h"
#include "PauseMenuState.h"
#include <iostream>

Engine::Engine(sf::Uint32 win_width, sf::Uint32 win_height, sf::String win_title)
{
	// Create window from width, height and title parameters
	m_window.create(sf::VideoMode(win_width, win_height), win_title, sf::Style::Default);
	// Disable key repeat
	m_window.setKeyRepeatEnabled(false);

	// Set key states to false initially
	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		m_keys[i].pressed = false;
		m_keys[i].released = false;
	}
	for (int i = 0; i < sf::Mouse::ButtonCount; i++)
	{
		m_mouse[i].released = false;
		m_mouse[i].pressed = false;
	}
}

void Engine::ChangeState(State state)
{
	// Remove 'active' states, ensuring the vector
	// isn't already empty when popping off states
	while (!m_states.empty())
		m_states.pop_back();

	// Push desred state onto vector
	switch (state)
	{
	case STATE_GAME:
		m_states.push_back(state_ptr(new GameState()));
		break;
	case STATE_ENDGAME:
		m_states.push_back(state_ptr(new EndGameState(this)));
		break;
	case STATE_MAINMENU:
		m_states.push_back(state_ptr(new MainMenuState(this)));
		break;
	case STATE_SCORES:
		m_states.push_back(state_ptr(new ScoresState(this)));
		break;
	case STATE_PAUSE:
		m_states.push_back(state_ptr(new PauseMenuState(this)));
		break;
	default:
		// If no state given, close and return error
		m_window.close();
		std::cerr << "ERROR: Failed to change state!" << std::endl;
		break;
	}

	// Initialise the new state
	m_states.back()->Init();
}

void Engine::PushState(State state)
{
	// NOTE: States aren't cleared so the previous state
	// is 'frozen' underneath the new active state

	// Push desired state onto vector
	switch (state)
	{
	case STATE_GAME:
		m_states.push_back(state_ptr(new GameState()));
		break;
	case STATE_ENDGAME:
		m_states.push_back(state_ptr(new EndGameState(this)));
		break;
	case STATE_MAINMENU:
		m_states.push_back(state_ptr(new MainMenuState(this)));
		break;
	case STATE_SCORES:
		m_states.push_back(state_ptr(new ScoresState(this)));
		break;
	case STATE_PAUSE:
		m_states.push_back(state_ptr(new PauseMenuState(this)));
		break;
	default:
		// Return error if no state is given
		std::cerr << "ERROR: Failed to push state!" << std::endl;
		break;
	}

	// Initialise the new state
	m_states.back()->Init();
}

void Engine::PopState()
{
	// Clear state at back of vector if
	// the vector is not empty
	if (!m_states.empty())
		m_states.pop_back();
}

void Engine::HandleEvents()
{
	// Call state's function if available
	if (!m_states.empty())
		m_states.back()->HandleEvents(this);

	// Reset key states
	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
		m_keys[i].released = false;
	for (int i = 0; i < sf::Mouse::ButtonCount; i++)
		m_mouse[i].released = false;

	// Run through SFML event queue on each frame
	while (m_window.pollEvent(m_event))
	{
		// Handle each event type
		switch (m_event.type)
		{
		case sf::Event::KeyPressed:
			m_keys[m_event.key.code].pressed = true;
			break;
		case sf::Event::KeyReleased:
			m_keys[m_event.key.code].released = true;
			m_keys[m_event.key.code].pressed = false;
			break;
		case sf::Event::MouseMoved:
			m_mousepos.x = m_event.mouseMove.x;
			m_mousepos.y = m_event.mouseMove.y;
			break;
		case sf::Event::MouseButtonPressed:
			m_mouse[m_event.mouseButton.button].pressed = true;
			break;
		case sf::Event::MouseButtonReleased:
			m_mouse[m_event.mouseButton.button].released = true;
			m_mouse[m_event.mouseButton.button].pressed = false;
			break;
		case sf::Event::TextEntered:
			if (use_text_buffer)
			{
				// IF the text buffer is enabled, record user inputs into the variable "text_buffer"
				if (m_event.text.unicode == 8)
				{
					// Remove the last character if backspace is pressed
					// ensuring "text_buffer" is not already empty
					if (!text_buffer.empty())
						text_buffer.pop_back();
				}
				// Add the input key into the "text_buffer" unless it is a carriage return or space
				// If the string exceeds 14 characters, prevent more characters from being input
				else if (m_event.text.unicode != 32 && m_event.text.unicode != 13
					&& text_buffer.length() < 15)
					text_buffer += static_cast<char>(m_event.text.unicode);
			}
			break;
		case sf::Event::Closed:
			// Close window on request
			m_window.close();
			break;
		default:
			// Ignore if no events in queue
			break;
		}
	}
}

void Engine::Update(float dt)
{
	// Call 'Update' if available
	if (!m_states.empty())
		m_states.back()->Update(this, dt);
}

void Engine::Draw()
{
	// Clear previous frame buffer
	m_window.clear(sf::Color::White);

	// Draw to hidden buffer if state available
	for (auto &s : m_states)
		s->Draw(this);

	// Swap frame buffers
	m_window.display();
}

bool Engine::IsRunning()
{
	return m_window.isOpen();
}

sf::RenderWindow* Engine::GetWindow()
{
	return &m_window;
}

bool Engine::GetReleased(unsigned int keycode)
{
	return m_keys[keycode].released;
}

bool Engine::GetPressed(unsigned int keycode)
{
	return m_keys[keycode].pressed;
}

bool Engine::GetMouseReleased(unsigned int keycode)
{
	return m_mouse[keycode].released;
}

bool Engine::GetMousePressed(unsigned int keycode)
{
	return m_mouse[keycode].pressed;
}

sf::Vector2i Engine::GetMousePos()
{
	return m_mousepos;
}