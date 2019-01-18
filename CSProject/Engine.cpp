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

	// Check joystick connected
	if (sf::Joystick::isConnected(0))
		use_joystick = true;

	// Set key states to false initially
	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		m_buttons[i].pressed = false;
		m_buttons[i].released = false;
		m_buttons[i].latch = false;
	}
}

void Engine::ChangeState(State state)
{
	// Remove 'active' states, ensuring the vector
	// isn't already empty when popping off states
	while (!m_states.empty())
		m_states.pop_back();

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

	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		m_buttons[i].released = false;
	}

	// Run through SFML event queue on each frame
	while (m_window.pollEvent(m_event))
	{
		// Handle each event type
		switch (m_event.type)
		{
		// Set keys pressed
		case sf::Event::KeyPressed:
			if (!use_joystick)
			{
				switch (m_event.key.code)
				{
				case sf::Keyboard::A:
					m_buttons[LEFT].pressed = true;
					break;
				case sf::Keyboard::D:
					m_buttons[RIGHT].pressed = true;
					break;
				case sf::Keyboard::W:
					m_buttons[JUMP].pressed = true;
					m_buttons[UP].pressed = true;
					break;
				case sf::Keyboard::S:
					m_buttons[DOWN].pressed = true;
					break;
				case sf::Keyboard::Enter:
					m_buttons[CONTINUE].pressed = true;
					break;
				case sf::Keyboard::Escape:
					m_buttons[BACK].pressed = true;
					break;
				}
			}
			break;
		case sf::Event::KeyReleased:
			if (!use_joystick)
			{
				switch (m_event.key.code)
				{
				case sf::Keyboard::A:
					m_buttons[LEFT].released = true;
					m_buttons[LEFT].pressed = false;
					break;
				case sf::Keyboard::D:
					m_buttons[RIGHT].released = true;
					m_buttons[RIGHT].pressed = false;
					break;
				case sf::Keyboard::W:
					m_buttons[JUMP].released = true;
					m_buttons[UP].released = true;
					m_buttons[JUMP].pressed = false;
					m_buttons[UP].pressed = false;
					break;
				case sf::Keyboard::S:
					m_buttons[DOWN].released = true;
					m_buttons[DOWN].pressed = false;
					break;
				case sf::Keyboard::Enter:
					m_buttons[CONTINUE].released = true;
					m_buttons[DOWN].pressed = false;
					break;
				case sf::Keyboard::Escape:
					m_buttons[BACK].released = true;
					m_buttons[BACK].pressed = false;
					break;
				}
			}
			break;
		case sf::Event::JoystickButtonPressed:
			if (use_joystick)
			{
				switch (m_event.joystickButton.button)
				{
				case sf::Joystick::Y:
					m_buttons[CONTINUE].pressed = true;
					m_buttons[JUMP].pressed = true;
					break;
				case sf::Joystick::Z:
					m_buttons[BACK].pressed = true;
					break;
				}
			}
			break;
		case sf::Event::JoystickButtonReleased:
			if (use_joystick)
			{
				switch (m_event.joystickButton.button)
				{
				case sf::Joystick::Y:
					m_buttons[CONTINUE].released = true;
					m_buttons[JUMP].released = true;
					m_buttons[CONTINUE].pressed = false;
					m_buttons[JUMP].pressed = false;
					break;
				case sf::Joystick::Z:
					m_buttons[BACK].pressed = false;
					m_buttons[BACK].released = true;
					break;
				}
			}
			break;
		case sf::Event::JoystickMoved:
			if (use_joystick)
			{
				switch (m_event.joystickMove.axis)
				{
				case sf::Joystick::Y:
					if (m_event.joystickMove.position == -100)
					{
						m_buttons[UP].pressed = true;
					}
					else if (m_event.joystickMove.position == 100)
					{
						m_buttons[DOWN].pressed = true;
					}
					else
					{
						m_buttons[UP].released = true;
						m_buttons[UP].pressed = false;
						m_buttons[DOWN].released = true;
						m_buttons[DOWN].pressed = false;
					}
					break;
				case sf::Joystick::PovY:
					if (m_event.joystickMove.position == 100)
					{
						m_buttons[UP].pressed = true;
					}
					else if (m_event.joystickMove.position == -100)
					{
						m_buttons[DOWN].pressed = true;
					}
					else
					{
						m_buttons[UP].released = true;
						m_buttons[UP].pressed = false;
						m_buttons[DOWN].released = true;
						m_buttons[DOWN].pressed = false;
					}
					break;
				case sf::Joystick::X:
				case sf::Joystick::PovX:
					if (m_event.joystickMove.position > 80)
					{
						m_buttons[RIGHT].pressed = true;
					}
					else if (m_event.joystickMove.position < -80)
					{
						m_buttons[LEFT].pressed = true;
					}
					else
					{
						m_buttons[RIGHT].released = true;
						m_buttons[RIGHT].pressed = false;
						m_buttons[LEFT].released = true;
						m_buttons[LEFT].pressed = false;
					}
					break;
				}
			}
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
					&& text_buffer.length() <= 15)
					text_buffer += static_cast<char>(m_event.text.unicode);
			}
			break;
		case sf::Event::Closed:
			// Close window on request
			m_window.close();
			break;
		case sf::Event::JoystickConnected:
			use_joystick = true;
			break;
		case sf::Event::JoystickDisconnected:
			use_joystick = false;
			break;
		default:
			// Ignore if no events in queue
			break;
		}

		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			if (m_buttons[i].released)
				m_buttons[i].latch = false;
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
	return m_buttons[keycode].released;
}

bool Engine::GetPressed(unsigned int keycode)
{
	if (!m_buttons[keycode].latch)
		return m_buttons[keycode].pressed;

	return false;
}

void Engine::SetLatch(unsigned int keycode)
{
	m_buttons[keycode].latch = true;
}

void Engine::ReleaseLatch(unsigned int keycode)
{
	m_buttons[keycode].latch = false;
}