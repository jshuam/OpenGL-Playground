#pragma once

#include <glm/vec3.hpp>

class Light
{
public:
	Light() = default;
	Light( glm::vec3 position, glm::vec3 colour );
	const glm::vec3& getPosition() const;
	const glm::vec3& getColour() const;

private:
	glm::vec3 position;
	glm::vec3 colour;
};

