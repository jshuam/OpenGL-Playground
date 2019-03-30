#include "WaterTile.h"

WaterTile::WaterTile( GLfloat center_x, GLfloat center_z, GLfloat height )
	:
	x( center_x ),
	z( center_z ),
	height( height )
{

}

const GLfloat& WaterTile::getHeight() const
{
	return height;
}

const GLfloat& WaterTile::getX() const
{
	return x;
}

const GLfloat& WaterTile::getZ() const
{
	return z;
}
