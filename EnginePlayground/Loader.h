#pragma once

#include <glad/glad.h>
#include <vector>
#include "RawModel.h"
#include "tiny_obj_loader.h"
#include "TextureData.h"

class Loader
{
public:
	RawModel loadToVAO( const std::vector<GLfloat>& vertices, GLuint dimensions );
	RawModel loadToVAO( const std::vector<GLfloat>& vertices, const std::vector<GLint>& indices,
						const std::vector<GLfloat>& tex_coords, const std::vector<GLfloat>& normals );
	void cleanUp();
	GLuint loadTexture( std::string filename );
	TextureData loadPNGFile( std::string filename );
	GLuint loadCubeMap( std::vector<std::string> cubeMapTextures );

private:
	GLuint createVAO();
	void storeDataInAttributeList( GLuint attribute_number, GLuint coordinate_size, const std::vector<tinyobj::real_t>& data );
	void unbindVAO();
	void bindIndicesBuffer( const std::vector<GLint>& indices );
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
	std::vector<GLuint> textures;
};

