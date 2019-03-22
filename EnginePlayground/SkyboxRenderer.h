#pragma once

#include "Camera.h"
#include "Loader.h"
#include "RawModel.h"
#include "SkyboxShader.h"

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <vector>

class SkyboxRenderer
{
public:
	SkyboxRenderer( Loader& loader, const glm::mat4& projection_matrix );

	void render( const Camera& camera );

private:
	static constexpr const GLfloat SIZE = 500.0f;

	const std::vector<GLfloat> VERTICES = {
		-SIZE,  SIZE, -SIZE,
		-SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		 SIZE, -SIZE, -SIZE,
		 SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,

		-SIZE, -SIZE,  SIZE,
		-SIZE, -SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE,  SIZE,
		-SIZE, -SIZE,  SIZE,

		 SIZE, -SIZE, -SIZE,
		 SIZE, -SIZE,  SIZE,
		 SIZE,  SIZE,  SIZE,
		 SIZE,  SIZE,  SIZE,
		 SIZE,  SIZE, -SIZE,
		 SIZE, -SIZE, -SIZE,

		-SIZE, -SIZE,  SIZE,
		-SIZE,  SIZE,  SIZE,
		 SIZE,  SIZE,  SIZE,
		 SIZE,  SIZE,  SIZE,
		 SIZE, -SIZE,  SIZE,
		-SIZE, -SIZE,  SIZE,

		-SIZE,  SIZE, -SIZE,
		 SIZE,  SIZE, -SIZE,
		 SIZE,  SIZE,  SIZE,
		 SIZE,  SIZE,  SIZE,
		-SIZE,  SIZE,  SIZE,
		-SIZE,  SIZE, -SIZE,

		-SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE,  SIZE,
		 SIZE, -SIZE, -SIZE,
		 SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE,  SIZE,
		 SIZE, -SIZE,  SIZE
	};

	const std::vector<std::string> TEXTURE_FILES =
	{
		"right",
		"left",
		"top",
		"bottom",
		"back",
		"front"
	};

	RawModel cube;
	GLuint texture;
	SkyboxShader shader;
};

