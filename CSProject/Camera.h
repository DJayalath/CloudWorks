#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "Bullet.h"

class Player;
class GameState;

class Camera
{
public:
	Camera();
	~Camera();

	sf::View GetView();
	void Update(GameState* state);
	sf::Vector2f GetCentre() { return m_view.getCenter(); }

	sf::Text GetDistText() { return m_dist_text; }
	sf::Text GetHealthText() { return m_kill_text; }
	sf::Text GetTimeText() { return m_time_text; }

private:

	void MoveCamera(Player* player);
	void MoveText(Player* player);
	void CheckBullets(std::list<Bullet>* bullets);

	sf::View m_view;
	sf::Font m_score_font;
	sf::Text m_dist_text;
	sf::Text m_kill_text;
	sf::Text m_time_text;
};

