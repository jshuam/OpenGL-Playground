#include "Camera.h"

Camera::Camera()
	:
	position{ 50, 1, 50 }
{}

void Camera::move()
{
	if( DisplayManager::getKey( GLFW_KEY_W ) == GLFW_PRESS )
	{
		position.z -= 1.5f;
	}
	if( DisplayManager::getKey( GLFW_KEY_S ) == GLFW_PRESS )
	{
		position.z += 1.5f;
	}
	if( DisplayManager::getKey( GLFW_KEY_D ) == GLFW_PRESS )
	{
		position.x += 1.5f;
	}
	if( DisplayManager::getKey( GLFW_KEY_A ) == GLFW_PRESS )
	{
		position.x -= 1.5f;
	}
	if( DisplayManager::getKey( GLFW_KEY_SPACE ) == GLFW_PRESS )
	{
		position.y += 1.5f;
	}
	if( DisplayManager::getKey( GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS )
	{
		position.y -= 1.5f;
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
