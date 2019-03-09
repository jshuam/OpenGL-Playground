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
	void prepare();
	void render( const Entity& entity, const StaticShader& shader );
};

