#include "Camera.h"

Camera::Camera()
	:
	position { 150, 1, 150 }
{}

void Camera::move( const GLfloat& dt )
{
	GLfloat local_speed = 2.0f;
	if( DisplayManager::getKey( GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS )
	{
		local_speed = boost_speed;
	}
	if( DisplayManager::getKey( GLFW_KEY_W ) == GLFW_PRESS )
	{
		position.z -= local_speed * dt;
	}
	if( DisplayManager::getKey( GLFW_KEY_S ) == GLFW_PRESS )
	{
		position.z += local_speed * dt;
	}
	if( DisplayManager::getKey( GLFW_KEY_D ) == GLFW_PRESS )
	{
		position.x += local_speed * dt;
	}
	if( DisplayManager::getKey( GLFW_KEY_A ) == GLFW_PRESS )
	{
		position.x -= local_speed * dt;
	}
	if( DisplayManager::getKey( GLFW_KEY_SPACE ) == GLFW_PRESS )
	{
		position.y += local_speed * dt;
	}
	if( DisplayManager::getKey( GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS )
	{
		position.y -= local_speed * dt;
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

GLfloat Camera::speed = 2.0f;
GLfloat Camera::boost_speed = 10.0f;
