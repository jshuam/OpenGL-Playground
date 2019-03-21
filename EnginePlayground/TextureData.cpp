#include "TextureData.h"

TextureData::TextureData( GLuint width, GLuint height, stbi_uc* buffer )
	:
	width( width ),
	height( height ),
	buffer( buffer )
{}

const GLuint& TextureData::getWidth() const
{
	return width;
}

const GLuint& TextureData::getHeight() const
{
	return height;
}

const stbi_uc* TextureData::getBuffer() const
{
	return buffer;
}
