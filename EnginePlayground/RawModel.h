#pragma once

#include <glad/glad.h>

class RawModel
{
public:
	RawModel() = default;
	RawModel( GLuint vao_id, GLuint vertex_count );
	GLuint getVaoId() const;
	GLuint getVertexCount() const;

private:
	GLuint vao_id;
	GLuint vertex_count;
};

