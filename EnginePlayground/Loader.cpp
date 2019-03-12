#include "Loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

RawModel Loader::loadToVAO( GLfloat* vertices, GLint* indices, GLfloat* tex_coords, GLint vert_count, GLint ind_count, GLint tex_count )
{
	GLuint vao_id = createVAO();
	bindIndicesBuffer( indices, ind_count );
	storeDataInAttributeList( 0, 3, vertices, vert_count );
	storeDataInAttributeList( 1, 2, tex_coords, tex_count );
	unbindVAO();
	return RawModel( vao_id, ind_count );
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
	filename += ".png";
	stbi_uc* data = stbi_load( filename.c_str(), &width, &height, &channels, 0 );

	if( data == nullptr )
	{
		throw( std::string( "Failed to load textures." ) );
	}

	GLint format = channels == 3 ? GL_RGB : GL_RGBA;

	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data );
	glGenerateMipmap( GL_TEXTURE_2D );
	stbi_image_free( data );

	textures.push_back( texture );
	return texture;
}

void Loader::storeDataInAttributeList( GLuint attribute_number, GLuint coordinate_size, GLfloat* data, GLint& count )
{
	GLuint vbo_id;
	glGenBuffers( 1, &vbo_id );
	vbos.push_back( vbo_id );
	glBindBuffer( GL_ARRAY_BUFFER, vbo_id );
	glBufferData( GL_ARRAY_BUFFER, sizeof( GLfloat ) * count, data, GL_STATIC_DRAW );
	glVertexAttribPointer( attribute_number, coordinate_size, GL_FLOAT, false, 0, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void Loader::unbindVAO()
{
	glBindVertexArray( 0 );
}

void Loader::bindIndicesBuffer( GLint* indices, GLint& count )
{
	GLuint vbo_id;
	glGenBuffers( 1, &vbo_id );
	vbos.push_back( vbo_id );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbo_id );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * count, indices, GL_STATIC_DRAW );
}
