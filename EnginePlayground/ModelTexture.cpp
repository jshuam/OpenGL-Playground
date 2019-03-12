#include "ModelTexture.h"

ModelTexture::ModelTexture( GLuint texture_id )
	:texture_id(texture_id)
{}

GLuint ModelTexture::getID()
{
	return texture_id;
}
