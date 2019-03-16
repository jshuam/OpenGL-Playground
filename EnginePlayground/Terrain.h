#pragma once

#include "Loader.h"
#include "ModelTexture.h"
#include "RawModel.h"
#include "TerrainTexture.h"
#include "TerrainTexturePack.h"

#include <GLFW/glfw3.h>

class Terrain
{
public:
	Terrain() = default;
	Terrain( GLuint x, GLuint z, Loader loader, TerrainTexturePack texture_pack, TerrainTexture blend_map );
	~Terrain() = default;

	const GLfloat& getX() const;
	const GLfloat& getZ() const;
	const RawModel& getModel() const;
	const TerrainTexture& getBlendMap() const;
	const TerrainTexturePack& getTexturePack() const;

private:
	RawModel generateTerrain( Loader loader );

private:
	static constexpr GLfloat SIZE = 800;
	static constexpr GLuint VERTEX_COUNT = 128;

	GLfloat x;
	GLfloat z;
	RawModel model;
	TerrainTexture blend_map;
	TerrainTexturePack texture_pack;
};

