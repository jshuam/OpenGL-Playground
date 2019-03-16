#pragma once

#include <GLFW/glfw3.h>

class TerrainTexture
{
public:
	TerrainTexture() = default;
	TerrainTexture( GLuint texture_id );

	const GLuint& getTextureId() const;

private:
	GLuint texture_id;
};

