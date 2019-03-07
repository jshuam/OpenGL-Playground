#pragma once

#include <glad/glad.h>

class RawModel
{
public:
	RawModel( GLuint vao_id, GLuint vertex_count );
	GLuint getVaoId();
	GLuint getVertexCount();
	
private:
	GLuint vao_id;
	GLuint vertex_count;
};

