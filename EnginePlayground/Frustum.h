#pragma once

#include "Camera.h"
#include "Plane.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Frustum
{
private:
	enum Halfspace
	{
		NEGATIVE = -1,
		ON_PLANE = 0,
		POSITIVE = 1
	};

public:
	Frustum() = default;
	Frustum( glm::mat4 projection_matrix );
	bool withinFrustum( const glm::vec3& point ) const;
	void update( const Camera& camera );

private:
	void normalizePlane( Plane& plane );
	void extractPlanes( const glm::mat4& combo_matrix );
	Halfspace classifyPoint( const Plane& plane, const glm::vec3& point ) const;
	GLfloat distanceToPoint( const Plane& plane, const glm::vec3& point ) const;

private:
	static constexpr const GLuint num_planes = 6;
	Plane planes[num_planes];
	glm::mat4 projection_matrix;
};
