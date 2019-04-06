#include "Maths.h"
#include "Frustum.h"

void Frustum::setCamInternals( GLfloat angle, GLfloat ratio, GLfloat near_d, GLfloat far_d )
{
	this->ratio = ratio;
	this->angle = angle;
	this->near_d = near_d;
	this->far_d = far_d;

	tang = (GLfloat) glm::tan( glm::radians( angle ) * 0.5 );
	nh = near_d * tang;
	nw = nh * ratio;
	fh = far_d * tang;
	fw = fh * ratio;
}

void Frustum::setCamDef( const glm::vec3& p, const glm::vec3& l, const glm::vec3& u )
{
	glm::vec3 dir, nc, fc, x, y, z;
	z = p - l;
	z = glm::normalize( z );
	x = u * z;
	x = glm::normalize( x );
	y = z * x;

	nc = p - z * near_d;
	fc = p - z * far_d;

	ntl = nc + y * nh - x * nw;
	ntr = nc + y * nh + x * nw;
	nbl = nc - y * nh - x * nw;
	nbr = nc - y * nh + x * nw;

	ftl = fc + y * fh - x * fw;
	ftr = fc + y * fh + x * fw;
	fbl = fc - y * fh - x * fw;
	fbr = fc - y * fh + x * fw;

	pl[TOP].set3Points( ntr, ntl, ftl );
	pl[BOTTOM].set3Points( nbl, nbr, fbr );
	pl[LEFT].set3Points( ntl, nbl, fbl );
	pl[RIGHT].set3Points( nbr, ntr, fbr );
	pl[NEARP].set3Points( ntl, ntr, nbr );
	pl[FARP].set3Points( ftr, ftl, fbl );
}

int Frustum::pointInFrustum( const glm::vec3& p )
{
	int result = INSIDE;
	for( int i = 0; i < 6; i++ )
	{
		if( pl[i].distance( p ) < 0 )
		{
			return OUTSIDE;
		}
	}
	return result;
}