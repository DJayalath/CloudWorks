#pragma once

#include <map>
#include <string>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetManager
{
public:
	// Default constructor
	AssetManager();

	// Textures
	enum TextureType {BALL, PLAYER, BOMBER, ANVIL, SPIKE, PLANK, MAX_TEXTURES};
	static sf::Texture m_textures[MAX_TEXTURES];
	
	// Sounds
	enum SoundType { HIT, JUMP, LOSE, BLIP, SWITCH, MAX_SOUNDS };
	static sf::Sound m_sounds[MAX_SOUNDS];

	// Music
	enum MusicType {MAIN, MAX_MUSIC};
	static sf::Music m_music[MAX_MUSIC];

	// Fonts
	enum FontType {JOYSTIX, MAX_FONTS};
	static sf::Font m_fonts[MAX_FONTS];

private:
	static sf::SoundBuffer m_soundbuffer[MAX_SOUNDS];
};