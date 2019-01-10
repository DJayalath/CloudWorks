#pragma once

#include <map>
#include <string>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetManager
{
public:
	AssetManager();

	std::map<std::string, sf::Texture> texture_map;
	std::map<std::string, sf::Sound> sound_map;

private:

	sf::Texture tex_ball;
	sf::Texture tex_player;
	sf::Texture tex_bomber;
	sf::Texture tex_anvil;
	sf::Texture tex_spike;

	sf::SoundBuffer hit;
	sf::Sound sound_hit;
	sf::SoundBuffer jump;
	sf::Sound sound_jump;
	sf::SoundBuffer lose;
	sf::Sound sound_lose;
	sf::SoundBuffer blip;
	sf::Sound sound_blip;
};
