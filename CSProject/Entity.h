#pragma once

#include <SFML/Graphics.hpp>

class GameState;
class Entity
{
public:
	// Constructor takes and sets initial position, scale and texture of entity
	Entity(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture);
	~Entity();

	// Pure virtual function must be overriden by children
	virtual void Update(GameState* state, float dt) = 0;

	// Attribute getters
	sf::Sprite& GetSprite();
	sf::FloatRect GetBounds();
	sf::Vector2f& GetPosition();
	sf::Vector2f& GetVelocity();
	float GetHealth();

	// Attribute setters
	void SetPosition(float x, float y);
	void SetVelocity(float v_x, float v_y);

protected:
	// Attributes
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	float m_health;
};