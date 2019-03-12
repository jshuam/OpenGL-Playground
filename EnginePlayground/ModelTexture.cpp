#include "ModelTexture.h"

ModelTexture::ModelTexture( GLuint texture_id )
	:
	texture_id( texture_id ),
	shine_damper( 1 ),
	reflectivity( 0 )
{}

GLuint ModelTexture::getID()
{
	return texture_id;
}

void ModelTexture::setShineDamper( const GLfloat& shine_damper )
{
	this->shine_damper = shine_damper;
}

void ModelTexture::setReflectivity( const GLfloat& reflectivity )
{
	this->reflectivity = reflectivity;
}

const GLfloat& ModelTexture::getShineDamper() const
{
	return shine_damper;
}

const GLfloat& ModelTexture::getReflectivity() const
{
	return reflectivity;
}
