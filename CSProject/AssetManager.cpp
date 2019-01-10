#include "AssetManager.h"

AssetManager::AssetManager()
{
	tex_ball.loadFromFile("./res/textures/ball.png");
	texture_map.insert(std::make_pair("Ball", tex_ball));
	tex_player.loadFromFile("./res/textures/player.png");
	texture_map.insert(std::make_pair("Player", tex_player));
	tex_bomber.loadFromFile("./res/textures/bomber.png");
	texture_map.insert(std::make_pair("Bomber", tex_bomber));
	tex_anvil.loadFromFile("./res/textures/anvil.png");
	texture_map.insert(std::make_pair("Anvil", tex_anvil));
	tex_spike.loadFromFile("./res/textures/spike.png");
	texture_map.insert(std::make_pair("Spike", tex_spike));

	hit.loadFromFile("./res/sounds/hit.wav");
	sound_hit.setBuffer(hit);
	sound_map.insert(std::make_pair("Hit", sound_hit));
	jump.loadFromFile("./res/sounds/jump.wav");
	sound_jump.setBuffer(jump);
	sound_map.insert(std::make_pair("Jump", sound_jump));
	lose.loadFromFile("./res/sounds/lose.wav");
	sound_lose.setBuffer(lose);
	sound_map.insert(std::make_pair("Lose", sound_lose));
	blip.loadFromFile("./res/sounds/blip.wav");
	sound_blip.setBuffer(blip);
	sound_map.insert(std::make_pair("Blip", sound_blip));
}