#pragma once

#include "glm/matrix.hpp"
#include "glm/vec3.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

class Maths
{
public:
	static glm::mat4 createTransformationMatrix( glm::vec3 translation, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale );
};

