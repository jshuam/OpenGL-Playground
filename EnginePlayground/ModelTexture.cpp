#include "ModelTexture.h"

ModelTexture::ModelTexture( GLuint texture_id )
	:
	texture_id( texture_id )
{}

const GLuint& ModelTexture::getID() const
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
