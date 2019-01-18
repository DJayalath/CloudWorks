#pragma once

#include <SFML/Graphics.hpp>
#include <list>

class Player;
class GameState;

class Camera
{
public:
	Camera();
	~Camera();

	sf::View GetView();
	void Update(GameState* state, float dt);
	sf::Vector2f GetCentre() { return m_view.getCenter(); }

	sf::Text GetDistText() { return m_dist_text; }
	sf::Text GetHealthText() { return m_kill_text; }
	sf::Text GetTimeText() { return m_score_text; }

private:

	void MoveCamera(Player* player, float dt);
	void MoveText(Player* player);

	sf::View m_view;
	sf::Text m_dist_text;
	sf::Text m_kill_text;
	sf::Text m_score_text;
};

