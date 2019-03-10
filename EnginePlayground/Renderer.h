#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include "RawModel.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"
#include "Maths.h"

class Renderer
{
public:
	Renderer( StaticShader shader );
	void prepare();
	void render( const Entity& entity, const StaticShader& shader );

private:
	static constexpr float FOV = 70.0f;
	static constexpr float NEAR_PLANE = 0.1f;
	static constexpr float FAR_PLANE = 1000.0f;
	glm::mat4 projection_matrix;

	void createProjectionMatrix();
};

