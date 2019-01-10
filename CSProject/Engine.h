#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "AssetManager.h"

#include "ProgramState.h"

enum State {STATE_GAME, STATE_ENDGAME, STATE_MAINMENU, STATE_SCORES, STATE_PAUSE};

class Engine
{
public:

	Engine(sf::Uint32 win_width, sf::Uint32 win_height, sf::String win_title);

	void ChangeState(State state);
	void PushState(State state);
	void PopState();

	void HandleEvents();
	void Update(double dt);
	void Draw();

	sf::RenderWindow* GetWindow();

	bool IsRunning();

	// Text Buffer
	std::string GetTextBuffer() { return text_buffer; }
	void StartTextBuffer() { use_text_buffer = true; }
	void CloseTextBuffer()
	{ 
		ClearTextBuffer();
		use_text_buffer = false;
	}
	void ClearTextBuffer() { text_buffer.clear(); }

	void SetUserScore(double score) { user_score = score; }
	double GetUserScore() { return user_score; }

	bool GetReleased(unsigned int keycode);
	bool GetPressed(unsigned int keycode);
	bool GetMouseReleased(unsigned int keycode);
	bool GetMousePressed(unsigned int keycode);
	sf::Vector2i GetMousePos();

private:

	double user_score = 0;
	AssetManager m_assets;

	bool use_text_buffer = false;
	std::string text_buffer;

	typedef std::shared_ptr<ProgramState> state_ptr;
	std::vector<state_ptr> m_states;

	sf::RenderWindow m_window;
	sf::Event m_event;

	struct KeyState
	{
		bool pressed;
		bool released;
	} m_keys[sf::Keyboard::KeyCount], m_mouse[sf::Mouse::ButtonCount];
	bool m_key_newstate;

	sf::Vector2i m_mousepos;
};

