#include "Light.h"

Light::Light( glm::vec3 position, glm::vec3 colour )
	:
	position( position ),
	colour( colour ),
	attenuation( 1, 0, 0 )
{}

Light::Light( glm::vec3 position, glm::vec3 colour, glm::vec3 attenuation )
	:
	position( position ),
	colour( colour ),
	attenuation( attenuation)
{}

const glm::vec3 & Light::getPosition() const
{
	return position;
}

const glm::vec3 & Light::getColour() const
{
	return colour;
}

const glm::vec3& Light::getAttenuation() const
{
	return attenuation;
}
