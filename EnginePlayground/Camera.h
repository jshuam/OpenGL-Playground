#pragma once

#include "DisplayManager.h"
#include <glm/vec3.hpp>

class Camera
{
public:
	Camera();
	void move( const GLfloat& dt );

	const glm::vec3& getPosition() const;
	const GLfloat& getPitch() const;
	const GLfloat& getYaw() const;
	const GLfloat& getRoll() const;

private:
	glm::vec3 position;
	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;
	static GLfloat speed;
	static GLfloat boost_speed;
};

