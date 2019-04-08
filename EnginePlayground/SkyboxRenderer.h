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
	SkyboxRenderer() = default;
	SkyboxRenderer( Loader loader, glm::mat4 projection_matrix );
	~SkyboxRenderer() = default;

	void render( const Camera& camera, const glm::vec3& fog_colour, const bool& cell_shading );

public:
	SkyboxShader shader;

private:
	void bindTextures();

private:
	static constexpr const GLfloat SIZE = 500.0f;

	std::vector<GLfloat> VERTICES = {
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

	std::vector<std::string> DAY_TEXTURE_FILES =
	{
		"right",
		"left",
		"top",
		"bottom",
		"back",
		"front"
	};

	std::vector<std::string> NIGHT_TEXTURE_FILES =
	{
		"nightRight",
		"nightLeft",
		"nightTop",
		"nightBottom",
		"nightBack",
		"nightFront"
	};

	RawModel cube;
	GLuint day_texture;
	GLuint night_texture;
	GLfloat time = 0;
};

