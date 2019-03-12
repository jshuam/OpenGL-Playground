#include "Light.h"

Light::Light( glm::vec3 position, glm::vec3 colour )
	:
	position(position),
	colour(colour)
{}

const glm::vec3 & Light::getPosition() const
{
	return position;
}

const glm::vec3 & Light::getColour() const
{
	return colour;
}
