#include "Camera.h"
#include "Player.h"
#include "GameState.h"

#include <iostream>
#include <string>

Camera::Camera() :
	m_view(sf::Vector2f(640.f, 360.f), sf::Vector2f(1280.f, 720.f))
{
	if (!m_score_font.loadFromFile("./res/fonts/joystix.ttf"))
	{
		std::cout << "ERROR: Failed to load font" << std::endl;
	}

	// select the font
	m_dist_text.setFont(m_score_font); // font is a sf::Font
	m_health_text.setFont(m_score_font);

	// set the character size
	m_dist_text.setCharacterSize(24); // in pixels, not points!
	m_health_text.setCharacterSize(24);

	// set the color
	m_dist_text.setFillColor(sf::Color(93, 87, 107));
	m_health_text.setFillColor(sf::Color(93, 87, 107));

}
Camera::~Camera() {}

void Camera::Update(GameState* state)
{
	MoveCamera(state->GetPlayer());
	MoveText(state->GetPlayer());
	CheckBullets(state->GetBullets());
}

void Camera::CheckBullets(std::list<Bullet>* bullets)
{
	for (auto &&b : *bullets)
	{
		if (b.GetPosition().x > m_view.getCenter().x + 680)
			b.SetDespawn(true);
		else if (b.GetPosition().x < m_view.getCenter().x - 680)
			b.SetDespawn(true);
		else if (b.GetPosition().y > m_view.getCenter().y + 400)
			b.SetDespawn(true);
		else if (b.GetPosition().y < m_view.getCenter().y - 400)
			b.SetDespawn(true);
	}
}

void Camera::MoveText(Player* player)
{
	m_dist_text.setString("Distance " + std::to_string(static_cast<int>(player->GetPosition().x)));
	m_health_text.setString("Health " + std::to_string(static_cast<int>(player->GetHealth())));
	m_dist_text.setPosition(m_view.getCenter().x + 380, m_view.getCenter().y - 350);
	m_health_text.setPosition(m_view.getCenter().x + 380, m_view.getCenter().y - 300);
}

void Camera::MoveCamera(Player* player)
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

	/* Stop player from moving behind camera by resetting position and
	eliminating their horizontal velocity */
	if (player_posx < cam_edgex)
	{
		player->SetVelocity(0, player->GetVelocity().y);
		player->SetPosition(cam_edgex, player->GetPosition().y);
	}
}

sf::View Camera::GetView()
{
	return m_view;
}