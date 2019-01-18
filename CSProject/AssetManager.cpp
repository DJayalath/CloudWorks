#include "AssetManager.h"

// Declare all static attributes (required in C++)
sf::Texture AssetManager::m_textures[AssetManager::MAX_TEXTURES];
sf::SoundBuffer AssetManager::m_soundbuffer[AssetManager::MAX_SOUNDS];
sf::Sound AssetManager::m_sounds[AssetManager::MAX_SOUNDS];
sf::Music AssetManager::m_music[AssetManager::MAX_MUSIC];
sf::Font AssetManager::m_fonts[AssetManager::MAX_FONTS];

AssetManager::AssetManager()
{
	// Load all textures into array
	m_textures[BALL].loadFromFile("./res/textures/ball.png");
	m_textures[PLAYER].loadFromFile("./res/textures/player.png");
	m_textures[BOMBER].loadFromFile("./res/textures/bomber.png");
	m_textures[ANVIL].loadFromFile("./res/textures/anvil.png");
	m_textures[SPIKE].loadFromFile("./res/textures/spike.png");
	m_textures[PLANK].loadFromFile("./res/textures/wooden_plank.png");

	// Load all sounds into sound buffer array
	m_soundbuffer[HIT].loadFromFile("./res/sounds/hit.wav");
	m_soundbuffer[JUMP].loadFromFile("./res/sounds/jump.wav");
	m_soundbuffer[BLIP].loadFromFile("./res/sounds/blip.wav");
	m_soundbuffer[LOSE].loadFromFile("./res/sounds/lose.wav");
	m_soundbuffer[SWITCH].loadFromFile("./res/sounds/switch.wav");

	// Set sound buffers in sound array
	for (int i = 0; i < MAX_SOUNDS; i++)
		m_sounds[i].setBuffer(m_soundbuffer[i]);

	// Load music into music array
	m_music[MAIN].openFromFile("./res/sounds/Toni_Leys-Through_A_Cardboard_World.wav");
	m_music[MAIN].setVolume(10.f);
	m_music[MAIN].setLoop(true);

	// Load fonts into font array
	m_fonts[JOYSTIX].loadFromFile("./res/fonts/joystix.ttf");
}