#include "DisplayManager.h"
#include "Player.h"

#include <glm/trigonometric.hpp>

Player::Player( TexturedModel model, glm::vec3 position, GLfloat rot_x, GLfloat rot_y, GLfloat rot_z, GLfloat scale )
	:
	Entity( model, position, rot_x, rot_y, rot_z, scale )
{}

void Player::move( const GLfloat& dt, const Terrain& terrain )
{
	checkInputs();
	increaseRotation( 0, current_turn_speed * dt, 0 );
	GLfloat distance = current_speed * dt;
	GLfloat dx = distance * glm::sin( glm::radians( getRotY() ) );
	GLfloat dz = distance * glm::cos( glm::radians( getRotY() ) );
	increasePosition( dx, 0, dz );
	upwards_speed += GRAVITY * dt;
	increasePosition( 0, upwards_speed * dt, 0 );
	GLfloat terrain_height = terrain.getTerrainHeight( getPosition().x, getPosition().z );
	if( getPosition().y < terrain_height )
	{
		upwards_speed = 0;
		in_air = false;
		setPosY( terrain_height );
	}
}

void Player::checkInputs()
{
	if( DisplayManager::getKey( GLFW_KEY_W ) == GLFW_PRESS && DisplayManager::getKey( GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS )
	{
		this->current_speed = BOOST_SPEED;
	}
	else if( DisplayManager::getKey( GLFW_KEY_S ) == GLFW_PRESS && DisplayManager::getKey( GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS )
	{
		this->current_speed = -BOOST_SPEED;
	}
	else if( DisplayManager::getKey( GLFW_KEY_W ) == GLFW_PRESS )
	{
		this->current_speed = RUN_SPEED;
	}
	else if( DisplayManager::getKey( GLFW_KEY_S ) == GLFW_PRESS )
	{
		this->current_speed = -RUN_SPEED;
	}
	else
	{
		this->current_speed = 0;
	}

	if( DisplayManager::getKey( GLFW_KEY_D ) == GLFW_PRESS )
	{
		this->current_turn_speed = -TURN_SPEED;
	}
	else if( DisplayManager::getKey( GLFW_KEY_A ) == GLFW_PRESS )
	{
		this->current_turn_speed = TURN_SPEED;
	}
	else
	{
		this->current_turn_speed = 0;
	}

	if( !in_air && DisplayManager::getKey( GLFW_KEY_SPACE ) == GLFW_PRESS )
	{
		jump();
		in_air = true;
	}
}

void Player::jump()
{
	upwards_speed = JUMP_POWER;
}
