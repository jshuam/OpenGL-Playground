#include "Plane.h"

#include <glm/geometric.hpp>

Plane::Plane( glm::vec3& v1, glm::vec3& v2, glm::vec3& v3 )
{
	set3Points( v1, v2, v3 );
}

void Plane::set3Points( glm::vec3& v1, glm::vec3& v2, glm::vec3& v3 )
{
	glm::vec3 aux1, aux2;

	aux1 = v1 - v2;
	aux2 = v3 - v2;

	normal = aux2 * aux1;

	normal = glm::normalize( normal );
	point = v2;
	d = -( normal.x * point.x + normal.y * point.y + normal.z * point.z );
}

void Plane::setNormalAndPoint( glm::vec3& normal, glm::vec3& point )
{
	this->normal = normal;
	this->normal = glm::normalize( this->normal );
	d = -( this->normal.x * point.x + this->normal.y * point.y + this->normal.z * point.z );
}

void Plane::setCoefficients( GLfloat a, GLfloat b, GLfloat c, GLfloat d )
{
	normal = glm::vec3( a, b, c );
	GLfloat l = glm::length( normal );
	normal = glm::vec3( a / l, b / l, c / l );
	this->d = d / l;
}

GLfloat Plane::distance( const glm::vec3& p )
{
	return ( d + ( normal.x * p.x + normal.y * p.y + normal.z * p.z ) );
}
