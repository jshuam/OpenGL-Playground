#pragma once

#include "Camera.h"
#include "Plane.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Frustum
{
private:

	enum
	{
		TOP = 0,
		BOTTOM,
		LEFT,
		RIGHT,
		NEARP,
		FARP
	};

public:

	static enum { OUTSIDE, INTERSECT, INSIDE };

	Plane pl[6];

	glm::vec3 ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
	GLfloat near_d, far_d, ratio, angle, tang;
	GLfloat nw, nh, fw, fh;

	Frustum() = default;
	~Frustum() = default;

	void setCamInternals( GLfloat angle, GLfloat ratio, GLfloat near_d, GLfloat far_d );
	void setCamDef( const glm::vec3& p, const glm::vec3& l, const glm::vec3& u );
	int pointInFrustum( const glm::vec3& p );
};
