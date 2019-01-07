#pragma once

#include <SFML/Graphics.hpp>

class GameState;
class Entity
{
public:

	Entity(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture);
	~Entity();

	// Pure virtual function must be overriden by children
	virtual void Update(GameState* state, double dt) = 0;

	sf::Sprite& GetSprite();
	sf::FloatRect GetBounds();
	sf::Vector2f GetPosition();
	sf::Vector2f GetVelocity();
	float GetHealth();

	void SetPosition(float x, float y);
	void SetVelocity(float v_x, float v_y);

protected:

	sf::Vector2f m_position;
	sf::Vector2f m_position_last;
	sf::Vector2f m_velocity;
	float m_health;

	sf::Sprite m_sprite;
};