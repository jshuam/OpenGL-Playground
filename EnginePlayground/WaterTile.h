#pragma once

#include <glad/glad.h>

class WaterTile
{
public:
	WaterTile( GLfloat center_x, GLfloat center_z, GLfloat height );

public:
	static constexpr const GLfloat TILE_SIZE = 60;

	const GLfloat& getHeight() const;
	const GLfloat& getX() const;
	const GLfloat& getZ() const;

private:
	GLfloat height;
	GLfloat x, z;
};

