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

void ModelTexture::setTransparency( const GLboolean& has_transparency )
{
	this->has_transparency = has_transparency;
}

void ModelTexture::setFakeLighting( const GLboolean& use_fake_lighting )
{
	this->use_fake_lighting = use_fake_lighting;
}

const GLboolean& ModelTexture::hasTransparency() const
{
	return has_transparency;
}

const GLboolean& ModelTexture::hasFakeLighting() const
{
	return use_fake_lighting;
}

const GLfloat& ModelTexture::getShineDamper() const
{
	return shine_damper;
}

const GLfloat& ModelTexture::getReflectivity() const
{
	return reflectivity;
}
