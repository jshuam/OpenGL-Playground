#include "Camera.h"

Camera::Camera()
	:
	position { 50, 1, 50 }
{}

void Camera::move( const GLfloat& delta_time )
{
	this->delta_time -= delta_time;
	if( DisplayManager::getKey( GLFW_KEY_W ) == GLFW_PRESS )
	{
		position.z -= speed * delta_time;
	}
	if( DisplayManager::getKey( GLFW_KEY_S ) == GLFW_PRESS )
	{
		position.z += speed * delta_time;
	}
	if( DisplayManager::getKey( GLFW_KEY_D ) == GLFW_PRESS )
	{
		position.x += speed * delta_time;
	}
	if( DisplayManager::getKey( GLFW_KEY_A ) == GLFW_PRESS )
	{
		position.x -= speed * delta_time;
	}
	if( DisplayManager::getKey( GLFW_KEY_SPACE ) == GLFW_PRESS )
	{
		position.y += speed * delta_time;
	}
	if( DisplayManager::getKey( GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS )
	{
		position.y -= speed * delta_time;
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
