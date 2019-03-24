#include "Camera.h"
#include "DisplayManager.h"

#include <glm/trigonometric.hpp>

Camera::Camera( Player* player )
	:
	player( player ),
	position { 0, 0, 0 }
{}

void Camera::move( const GLfloat& dt )
{
	if( DisplayManager::mouseScrolling() )
	{
		calculateZoom();
		DisplayManager::mouseScrolling() = false;
	}
	if( DisplayManager::mouseLClick() )
	{
		calculatePitch();
	}
	if( DisplayManager::mouseRClick() )
	{
		calculateAngleAroundPlayer();
	}
	GLfloat horizontal_distance = calculateHorizontalDistance();
	GLfloat vertical_distance = calculateVerticalDistance();
	calculateCameraPosition( horizontal_distance, vertical_distance );
	yaw = 180 - ( player->getRotY() + angle_around_player );
}

const glm::vec3& Camera::getPosition() const
{
	return position;
}

const GLfloat& Camera::getPitch() const
{
	return pitch;
}

const GLfloat& Camera::getYaw() const
{
	return yaw;
}

const GLfloat& Camera::getRoll() const
{
	return roll;
}

void Camera::calculateZoom()
{
	GLfloat zoom_level = DisplayManager::getMouseDWheel();
	distance_from_player -= zoom_level;
}

void Camera::calculatePitch()
{
	GLfloat pitch_change = DisplayManager::getMouseYOffset() * 0.3f;
	pitch -= pitch_change;
}

void Camera::calculateAngleAroundPlayer()
{
	GLfloat angle_change = DisplayManager::getMouseXOffset() * 0.3f;
	angle_around_player -= angle_change;
}

void Camera::calculateCameraPosition( const GLfloat& horizontal_distance, const GLfloat& vertical_distance )
{
	GLfloat theta = player->getRotY() + angle_around_player;
	GLfloat offset_x = horizontal_distance * glm::sin( glm::radians( theta ) );
	GLfloat offset_z = horizontal_distance * glm::cos( glm::radians( theta ) );
	position.x = player->getPosition().x - offset_x;
	position.z = player->getPosition().z - offset_z;
	position.y = player->getPosition().y + vertical_distance;
}

const GLfloat& Camera::calculateHorizontalDistance() const
{
	return distance_from_player * glm::cos( glm::radians( pitch ) );
}

const GLfloat& Camera::calculateVerticalDistance() const
{
	return distance_from_player * glm::sin( glm::radians( pitch ) );
}