#pragma once

#include <glad/glad.h>
#include <glm/vec3.hpp>

class Light
{
public:
	Light() = default;
	Light( glm::vec3 position, glm::vec3 colour );
	Light( glm::vec3 position, glm::vec3 colour, glm::vec3 attenuation );
	const glm::vec3& getPosition() const;
	const glm::vec3& getColour() const;
	const glm::vec3& getAttenuation() const;

	void setPosition( const glm::vec3& position );
	void setPosition( const GLfloat& x, const GLfloat& y, const GLfloat& z );

private:
	glm::vec3 position;
	glm::vec3 colour;
	glm::vec3 attenuation;
};

