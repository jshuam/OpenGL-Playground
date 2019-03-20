#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

class GuiTexture
{
public:
	GuiTexture( GLuint texture, glm::vec2 position, glm::vec2 scale );

public:
	const GLuint& getTexture() const;
	const glm::vec2& getPosition() const;
	const glm::vec2& getScale() const;

private:
	GLuint texture;
	glm::vec2 position;
	glm::vec2 scale;

};

