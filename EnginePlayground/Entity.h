#pragma once

#include "TexturedModel.h"
#include <glm/vec3.hpp>
#include <glad/glad.h>

class Entity
{
public:
	Entity() = default;
	Entity( TexturedModel model, glm::vec3 position, GLfloat rot_x, GLfloat rot_y, GLfloat rot_z, GLfloat scale );

	void increasePosition( const GLfloat& dx, const GLfloat& dy, const GLfloat& dz );
	void increaseRotation( const GLfloat& dx, const GLfloat& dy, const GLfloat& dz );

	const TexturedModel& getModel() const;
	const glm::vec3& getPosition() const;
	const GLfloat& getRotX() const;
	const GLfloat& getRotY() const;
	const GLfloat& getRotZ() const;
	const GLfloat& getScale() const;

private:
	TexturedModel model;
	glm::vec3 position;
	GLfloat rot_x, rot_y, rot_z;
	GLfloat scale;
};

