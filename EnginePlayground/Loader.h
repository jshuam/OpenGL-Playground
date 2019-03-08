#pragma once

#include <glad/glad.h>
#include <vector>
#include "RawModel.h"

class Loader
{
public:
	RawModel loadToVAO( const std::vector<GLfloat>& positions, const std::vector<GLfloat>& texture_coords, const std::vector<GLuint>& indices );
	void cleanUp();
	GLuint loadTexture( std::string filename );

private:
	GLuint createVAO();
	void storeDataInAttributeList( GLuint attribute_number, GLuint coordinate_size, const std::vector<GLfloat>& data );
	void unbindVAO();
	void bindIndicesBuffer( const std::vector<GLuint>& indices );
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
	std::vector<GLuint> textures;
};

