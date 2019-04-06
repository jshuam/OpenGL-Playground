#include "Maths.h"
#include "Frustum.h"

Frustum::Frustum( glm::mat4 projection_matrix )
	:
	projection_matrix( projection_matrix )
{}

Frustum::Halfspace Frustum::classifyPoint( const Plane& plane, const glm::vec3& point ) const
{
	GLfloat d;

	d = distanceToPoint( plane, point );

	if( d < 0 ) return NEGATIVE;
	if( d > 0 ) return POSITIVE;
	return ON_PLANE;
}

bool Frustum::withinFrustum( const glm::vec3& point ) const
{
	for( int i = 0; i < num_planes; i++ )
	{
		if( classifyPoint( planes[i], point ) == NEGATIVE )
		{
			return false;
		}
	}

	return true;
}

void Frustum::normalizePlane( Plane& plane )
{
	GLfloat mag;

	mag = glm::sqrt( plane.a * plane.a + plane.b * plane.b + plane.c * plane.c );

	plane.a = plane.a / mag;
	plane.b = plane.b / mag;
	plane.c = plane.c / mag;
	plane.d = plane.d / mag;
}

void Frustum::extractPlanes( const glm::mat4& combo_matrix )
{
	planes[0].a = combo_matrix[3][0] + combo_matrix[0][0];
	planes[0].b = combo_matrix[3][1] + combo_matrix[0][1];
	planes[0].c = combo_matrix[3][2] + combo_matrix[0][2];
	planes[0].d = combo_matrix[3][3] + combo_matrix[0][3];

	planes[1].a = combo_matrix[3][0] - combo_matrix[0][0];
	planes[1].b = combo_matrix[3][1] - combo_matrix[0][1];
	planes[1].c = combo_matrix[3][2] - combo_matrix[0][2];
	planes[1].d = combo_matrix[3][3] - combo_matrix[0][3];

	planes[2].a = combo_matrix[3][0] - combo_matrix[1][0];
	planes[2].b = combo_matrix[3][1] - combo_matrix[1][1];
	planes[2].c = combo_matrix[3][2] - combo_matrix[1][2];
	planes[2].d = combo_matrix[3][3] - combo_matrix[1][3];

	planes[3].a = combo_matrix[3][0] + combo_matrix[1][0];
	planes[3].b = combo_matrix[3][1] + combo_matrix[1][1];
	planes[3].c = combo_matrix[3][2] + combo_matrix[1][2];
	planes[3].d = combo_matrix[3][3] + combo_matrix[1][3];

	planes[4].a = combo_matrix[3][0] + combo_matrix[2][0];
	planes[4].b = combo_matrix[3][1] + combo_matrix[2][1];
	planes[4].c = combo_matrix[3][2] + combo_matrix[2][2];
	planes[4].d = combo_matrix[3][3] + combo_matrix[2][3];

	planes[5].a = combo_matrix[3][0] - combo_matrix[2][0];
	planes[5].b = combo_matrix[3][1] - combo_matrix[2][1];
	planes[5].c = combo_matrix[3][2] - combo_matrix[2][2];
	planes[5].d = combo_matrix[3][3] - combo_matrix[2][3];

	normalizePlane( planes[0] );
	normalizePlane( planes[1] );
	normalizePlane( planes[2] );
	normalizePlane( planes[3] );
	normalizePlane( planes[4] );
	normalizePlane( planes[5] );
}

void Frustum::update( const Camera& camera )
{
	glm::mat4 view_matrix = Maths::createViewMatrix( camera );
	glm::mat4 combo_matrix = projection_matrix * view_matrix;
	extractPlanes( combo_matrix );
}

GLfloat Frustum::distanceToPoint( const Plane& plane, const glm::vec3& point ) const
{
	return plane.a * point.x + plane.b * point.y + plane.c * point.z + plane.d;
}
