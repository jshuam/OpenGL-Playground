#pragma once

#include <glad/glad.h>

class ModelTexture
{
public:
	ModelTexture() = default;
	ModelTexture(GLuint texture_id);
	GLuint getID();

private:
	GLuint texture_id;
};

