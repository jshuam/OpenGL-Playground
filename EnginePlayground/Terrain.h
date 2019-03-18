#pragma once

#include "Loader.h"
#include "ModelTexture.h"
#include "RawModel.h"
#include "TerrainTexture.h"
#include "TerrainTexturePack.h"

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include "stb_image.h"

class Terrain
{
public:
	Terrain() = default;
	Terrain( GLuint x, GLuint z, Loader loader, TerrainTexturePack texture_pack, TerrainTexture blend_map, std::string height_map );
	~Terrain() = default;

	const GLfloat& getX() const;
	const GLfloat& getZ() const;
	const RawModel& getModel() const;
	const TerrainTexture& getBlendMap() const;
	const TerrainTexturePack& getTexturePack() const;
	const GLfloat& getTerrainHeight( const GLfloat& world_x, const GLfloat& world_z ) const;

private:
	RawModel generateTerrain( Loader loader, std::string height_map );
	GLfloat getHeight( GLuint x, GLuint y, stbi_uc* image, GLint image_width, GLint image_height );
	glm::vec3 calculateNormal( GLuint x, GLuint z, stbi_uc* image, GLint image_width, GLint image_height );

private:
	static constexpr GLfloat SIZE = 800;
	static constexpr GLfloat MAX_HEIGHT = 40;
	static constexpr GLfloat MAX_PIXEL_COLOUR = 127.5;

	GLint VERTEX_COUNT;
	GLfloat x;
	GLfloat z;
	RawModel model;
	TerrainTexture blend_map;
	TerrainTexturePack texture_pack;

	std::vector<GLfloat> heights;
};

