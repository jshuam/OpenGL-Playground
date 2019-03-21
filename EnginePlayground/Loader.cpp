#include "Loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

RawModel Loader::loadToVAO( const std::vector<GLfloat>& vertices, GLuint dimensions )
{
	GLuint vao_id = createVAO();
	storeDataInAttributeList( 0, dimensions, vertices );
	unbindVAO();
	return RawModel( vao_id, vertices.size() / dimensions );
}

RawModel Loader::loadToVAO( const std::vector<GLfloat>& vertices, const std::vector<GLint>& indices,
							const std::vector<GLfloat>& tex_coords, const std::vector<GLfloat>& normals )
{
	GLuint vao_id = createVAO();
	bindIndicesBuffer( indices );
	storeDataInAttributeList( 0, 3, vertices );
	storeDataInAttributeList( 1, 2, tex_coords );
	storeDataInAttributeList( 2, 3, normals );
	unbindVAO();
	return RawModel( vao_id, indices.size() );
}
GLuint Loader::createVAO()
{
	GLuint vao_id;
	glGenVertexArrays( 1, &vao_id );
	vaos.push_back( vao_id );
	glBindVertexArray( vao_id );
	return vao_id;
}

void Loader::cleanUp()
{
	for( auto& vao : vaos )
	{
		glDeleteVertexArrays( 1, &vao );
	}
	for( auto& vbo : vbos )
	{
		glDeleteBuffers( 1, &vbo );
	}
	for( auto& texture : textures )
	{
		glDeleteTextures( 1, &texture );
	}

	vaos.clear();
	vbos.clear();
	textures.clear();
}

GLuint Loader::loadTexture( std::string filename )
{
	GLint width, height, channels;
	GLuint texture;
	filename = "res/" + filename + ".png";
	stbi_uc* data = stbi_load( filename.c_str(), &width, &height, &channels, 0 );

	if( data == nullptr )
	{
		std::cerr << "Failed to load textures." << std::endl;
		std::cin.get();
		exit( -1 );
	}

	GLint format = channels == 3 ? GL_RGB : GL_RGBA;

	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f );
	glGenerateMipmap( GL_TEXTURE_2D );
	stbi_image_free( data );

	textures.push_back( texture );
	return texture;
}

TextureData Loader::loadPNGFile( std::string filename )
{
	GLint width, height, channels;
	stbi_uc* buffer = stbi_load( ( "res/" + filename + ".png" ).c_str(), &width, &height, &channels, 4 );
	if( channels != 4 )
	{
		std::cerr << "Cube Map Texture is not RGBA." << std::endl;
		std::cin.get();
		exit( -1 );
	}
	return TextureData( width, height, buffer );
}

GLuint Loader::loadCubeMap( std::vector<std::string> cubeMapTextures )
{
	GLuint tex_id;
	glGenTextures( 1, &tex_id );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_CUBE_MAP, tex_id );

	for( int i = 0; i < cubeMapTextures.size(); i++ )
	{
		TextureData data = loadPNGFile( cubeMapTextures[i] );
		glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, data.getWidth(), data.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data.getBuffer() );
	}
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	textures.push_back( tex_id );
	return tex_id;
}

void Loader::storeDataInAttributeList( GLuint attribute_number, GLuint coordinate_size, const std::vector<tinyobj::real_t>& data )
{
	GLuint vbo_id;
	glGenBuffers( 1, &vbo_id );
	vbos.push_back( vbo_id );
	glBindBuffer( GL_ARRAY_BUFFER, vbo_id );
	glBufferData( GL_ARRAY_BUFFER, data.size() * sizeof( GLfloat ), data.data(), GL_STATIC_DRAW );
	glVertexAttribPointer( attribute_number, coordinate_size, GL_FLOAT, false, 0, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void Loader::unbindVAO()
{
	glBindVertexArray( 0 );
}

void Loader::bindIndicesBuffer( const std::vector<GLint>& indices )
{
	GLuint vbo_id;
	glGenBuffers( 1, &vbo_id );
	vbos.push_back( vbo_id );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbo_id );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( GLint ), indices.data(), GL_STATIC_DRAW );
}
