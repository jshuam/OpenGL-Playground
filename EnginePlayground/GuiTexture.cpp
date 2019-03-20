#include "GuiTexture.h"

GuiTexture::GuiTexture( GLuint texture, glm::vec2 position, glm::vec2 scale )
	:
	texture(texture),
	position(position),
	scale(scale)
{}

const GLuint & GuiTexture::getTexture() const
{
	return texture;
}

const glm::vec2 & GuiTexture::getPosition() const
{
	return position;
}

const glm::vec2 & GuiTexture::getScale() const
{
	return scale;
}
