#include "TerrainTexture.h"

TerrainTexture::TerrainTexture( GLuint texture_id )
	:
	texture_id( texture_id )
{}

const GLuint& TerrainTexture::getTextureId() const
{
	return texture_id;
}
