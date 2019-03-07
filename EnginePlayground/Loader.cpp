#include "Loader.h"

RawModel Loader::loadToVAO( std::vector<GLfloat> positions )
{
	GLuint vao_id = createVAO();
	storeDataInAttributeList( 0, positions );
	unbindVAO();
	return RawModel( vao_id, positions.size() / 3 );
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
	glDeleteVertexArrays( vaos.size(), vaos.data() );
	glDeleteBuffers( vbos.size(), vbos.data() );
}

void Loader::storeDataInAttributeList( GLuint attribute_number, std::vector<GLfloat> data )
{
	GLuint vbo_id;
	glGenBuffers( 1, &vbo_id );
	vbos.push_back( vbo_id );
	glBindBuffer( GL_ARRAY_BUFFER, vbo_id );
	glBufferData( GL_ARRAY_BUFFER, sizeof( data ), data.data(), GL_STATIC_DRAW );
	glVertexAttribPointer( attribute_number, 3, GL_FLOAT, false, 0, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void Loader::unbindVAO()
{
	glBindVertexArray( 0 );
}
