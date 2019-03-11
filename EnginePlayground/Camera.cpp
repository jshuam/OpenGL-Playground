#include "Camera.h"

Camera::Camera()
{
	position = { 0, 0, 0 };
}

void Camera::move()
{
	if( DisplayManager::getKey( GLFW_KEY_W ) == GLFW_PRESS )
	{
		position.z -= 0.02f;
	}
	if( DisplayManager::getKey( GLFW_KEY_D ) == GLFW_PRESS )
	{
		position.x += 0.02f;
	}
	if( DisplayManager::getKey( GLFW_KEY_A ) == GLFW_PRESS )
	{
		position.x -= 0.02f;
	}
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
