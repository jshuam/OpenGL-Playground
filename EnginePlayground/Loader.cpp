#include "Loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

RawModel Loader::loadToVAO( const std::vector<GLfloat>& positions, const std::vector<GLfloat>& texture_coords, const std::vector<GLuint>& indices )
{
	GLuint vao_id = createVAO();
	bindIndicesBuffer( indices );
	storeDataInAttributeList( 0, 3, positions );
	storeDataInAttributeList( 1, 2, texture_coords );
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
	GLint width, height;
	GLuint texture;
	filename += ".png";
	unsigned char* data = stbi_load( filename.c_str(), &width, &height, 0, 0 );

	if( data == nullptr )
	{
		throw( std::string( "Failed to load textures." ) );
	}
	glActiveTexture( GL_TEXTURE0 );
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
	glGenerateMipmap( GL_TEXTURE_2D );
	stbi_image_free( data );

	textures.push_back( texture );
	return texture;
}

void Loader::storeDataInAttributeList( GLuint attribute_number, GLuint coordinate_size, const std::vector<GLfloat>& data )
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

void Loader::bindIndicesBuffer( const std::vector<GLuint>& indices )
{
	GLuint vbo_id;
	glGenBuffers( 1, &vbo_id );
	vbos.push_back( vbo_id );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbo_id );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( GLuint ), indices.data(), GL_STATIC_DRAW );
}
