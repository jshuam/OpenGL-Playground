#pragma once

#include <glad/glad.h>
#include <glm/vec3.hpp>

struct Plane
{
public:
	glm::vec3 normal, point;
	GLfloat d;

	Plane( glm::vec3& v1, glm::vec3& v2, glm::vec3& v3 );
	Plane() = default;
	~Plane() = default;

	void set3Points( glm::vec3& v1, glm::vec3& v2, glm::vec3& v3 );
	void setNormalAndPoint( glm::vec3& normal, glm::vec3& point );
	void setCoefficients( GLfloat a, GLfloat b, GLfloat c, GLfloat d );
	GLfloat distance( const glm::vec3& p );
};

