#pragma once

#include "Loader.h"
#include "ModelTexture.h"
#include "RawModel.h"

#include <GLFW/glfw3.h>

class Terrain
{
public:
	Terrain() = default;
	Terrain( GLuint x, GLuint z, Loader loader, ModelTexture texture );
	~Terrain() = default;

	const GLfloat& getX() const;
	const GLfloat& getZ() const;
	const RawModel& getModel() const;
	const ModelTexture& getTexture() const;

private:
	RawModel generateTerrain( Loader loader );

private:
	static constexpr GLfloat SIZE = 800;
	static constexpr GLuint VERTEX_COUNT = 128;

	GLfloat x;
	GLfloat z;
	RawModel model;
	ModelTexture texture;
};

