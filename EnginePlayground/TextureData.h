#pragma once

#include <glad/glad.h>
#include "stb_image.h"

class TextureData
{
public:
	TextureData( GLuint width, GLuint height, stbi_uc* buffer );
	
	const GLuint& getWidth() const;
	const GLuint& getHeight() const;
	const stbi_uc* getBuffer() const;

private:
	GLuint width;
	GLuint height;
	stbi_uc* buffer;
};

