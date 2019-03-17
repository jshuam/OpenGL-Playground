#include "Camera.h"
#include "DisplayManager.h"

Camera::Camera( Player player )
	:
	player( player ),
	position { 150, 15, 150 }
{}

void Camera::move( const GLfloat& dt )
{
	calculateZoom();
	calculatePitch();
	calculateAngleAroundPlayer();
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
	GLfloat zoom_level = DisplayManager::getMouseDWheel() * 0.1f;
	distance_from_player -= zoom_level;
}

void Camera::calculatePitch()
{
	if( DisplayManager::getKey( GLFW_MOUSE_BUTTON_2 ) == GLFW_PRESS )
	{
		GLfloat pitch_change = DisplayManager::getMouseYPos() * 0.1f;
		pitch -= pitch_change;
	}
}

void Camera::calculateAngleAroundPlayer()
{
	if( DisplayManager::getKey( GLFW_MOUSE_BUTTON_1 ) == GLFW_PRESS )
	{
		GLfloat angle_change = DisplayManager::getMouseXPos() * 0.3f;
		angle_around_player -= angle_change;
	}
}
