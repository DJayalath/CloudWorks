#pragma once

#include <map>
#include <string>
#include <utility>
#include <SFML/Graphics.hpp>

class AssetManager
{
public:

	AssetManager()
	{
		tex_sprite.loadFromFile("./res/PiskelSprite.png");
		texture_map.insert(std::make_pair("Sprite", tex_sprite));
		tex_ball.loadFromFile("./res/Ball.png");
		texture_map.insert(std::make_pair("Ball", tex_ball));
		tex_player.loadFromFile("./res/Player.png");
		texture_map.insert(std::make_pair("Player", tex_player));
	}

	std::map<std::string, sf::Texture> texture_map;

private:

	sf::Texture tex_sprite;
	sf::Texture tex_ball;
	sf::Texture tex_player;
};
