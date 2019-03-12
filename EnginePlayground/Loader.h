#pragma once

#include <glad/glad.h>
#include <vector>
#include "RawModel.h"
#include "tiny_obj_loader.h"

class Loader
{
public:
	RawModel loadToVAO( GLfloat* vertices, GLint* indices, GLfloat* tex_coords, GLint vert_count, GLint ind_count, GLint tex_count );
	void cleanUp();
	GLuint loadTexture( std::string filename );

private:
	GLuint createVAO();
	void storeDataInAttributeList( GLuint attribute_number, GLuint coordinate_size, GLfloat* data, GLint& count );
	void unbindVAO();
	void bindIndicesBuffer( GLint* indices, GLint& count );
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
	std::vector<GLuint> textures;
};

