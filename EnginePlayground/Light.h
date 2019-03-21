#pragma once

#include <glm/vec3.hpp>

class Light
{
public:
	Light() = default;
	Light( glm::vec3 position, glm::vec3 colour );
	Light( glm::vec3 position, glm::vec3 colour, glm::vec3 attenuation );
	const glm::vec3& getPosition() const;
	const glm::vec3& getColour() const;
	const glm::vec3& getAttenuation() const;

private:
	glm::vec3 position;
	glm::vec3 colour;
	glm::vec3 attenuation;
};

