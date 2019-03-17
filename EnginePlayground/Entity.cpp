#include "Entity.h"

Entity::Entity( TexturedModel model, glm::vec3 position, GLfloat rot_x, GLfloat rot_y, GLfloat rot_z, GLfloat scale )
{
	this->model = model;
	this->position = position;
	this->rot_x = rot_x;
	this->rot_y = rot_y;
	this->rot_z = rot_z;
	this->scale = scale;
}

void Entity::increasePosition( const GLfloat& dx, const GLfloat& dy, const GLfloat& dz )
{
	this->position.x += dx;
	this->position.y += dy;
	this->position.z += dz;
}

void Entity::increaseRotation( const GLfloat& dx, const GLfloat& dy, const GLfloat& dz )
{
	this->rot_x += dx;
	this->rot_y += dy;
	this->rot_z += dz;
}

const TexturedModel& Entity::getModel() const
{
	return model;
}

const glm::vec3& Entity::getPosition() const
{
	return position;
}

const GLfloat& Entity::getRotX() const
{
	return rot_x;
}

const GLfloat& Entity::getRotY() const
{
	return rot_y;
}

const GLfloat& Entity::getRotZ() const
{
	return rot_z;
}

const GLfloat& Entity::getScale() const
{
	return scale;
}

void Entity::setPosX( const GLfloat& x_pos )
{
	this->position.x = x_pos;
}

void Entity::setPosY( const GLfloat& y_pos )
{
	this->position.y = y_pos;
}

void Entity::setPosZ( const GLfloat& z_pos )
{
	this->position.z = z_pos;
}

