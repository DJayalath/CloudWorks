#include "Camera.h"
#include "Player.h"
#include "GameState.h"
#include "AssetManager.h"

#include <iostream>
#include <string>

Camera::Camera() :
	m_view(sf::Vector2f(640.f, 360.f), sf::Vector2f(1280.f, 720.f))
{
	// select the font
	m_dist_text.setFont(AssetManager::m_fonts[AssetManager::JOYSTIX]); // font is a sf::Font
	m_kill_text.setFont(AssetManager::m_fonts[AssetManager::JOYSTIX]);
	m_score_text.setFont(AssetManager::m_fonts[AssetManager::JOYSTIX]);

	// set the character size
	m_dist_text.setCharacterSize(24); // in pixels, not points!
	m_kill_text.setCharacterSize(24);
	m_score_text.setCharacterSize(24);

	// set the color
	m_dist_text.setFillColor(sf::Color(93, 87, 107));
	m_kill_text.setFillColor(sf::Color(93, 87, 107));
	m_score_text.setFillColor(sf::Color(93, 87, 107));

}
Camera::~Camera() {}

void Camera::Update(GameState* state, float dt)
{
	MoveCamera(state->GetPlayer(), dt);
	MoveText(state->GetPlayer());
}

void Camera::MoveText(Player* player)
{
	m_dist_text.setString("Distance\n" + std::to_string(static_cast<int>(player->GetPosition().x)));
	m_kill_text.setString("Time\n" + std::to_string(static_cast<int>(player->GetTime())));
	m_score_text.setString("Score\n" + std::to_string(static_cast<int>(player->GetPosition().x * 0.1f + 50.f * player->GetTime())));
	m_dist_text.setPosition(m_view.getCenter().x - 600, m_view.getCenter().y - 350);
	m_kill_text.setPosition(m_view.getCenter().x - 400, m_view.getCenter().y - 350);
	m_score_text.setPosition(m_view.getCenter().x - 250, m_view.getCenter().y - 350);
}

void Camera::MoveCamera(Player* player, float dt)
{
	/* Camera Control
	- If player moves beyond camera centre, the camera moves with player
	- Player is restricted from moving behind camera
	*/
	float player_posx = player->GetPosition().x;
	float cam_centrex = m_view.getCenter().x;
	float cam_edgex = cam_centrex - m_view.getSize().x / 2;

	// Move camera wth player if player moves past camera centre
	if (player_posx > cam_centrex)
		m_view.setCenter(sf::Vector2f(player_posx, m_view.getCenter().y));

	/* Stop player from moving behind camera by resetting their horizontal velocity */
	if (player_posx < cam_edgex)
		player->SetPosition(cam_edgex, player->GetPosition().y);

	// Naturally move camera all the time to keep player moving forward (speed increases with distance)
	m_view.move(sf::Vector2f(std::fminf(50.f + player->GetPosition().x / 100.f, 225.f) * dt, 0));
}

sf::View Camera::GetView()
{
	return m_view;
}