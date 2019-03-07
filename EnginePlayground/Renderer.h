#pragma once

#include <glad/glad.h>
#include "RawModel.h"
#include "TexturedModel.h"

class Renderer
{
public:
	void prepare();
	void render( const TexturedModel& textured_model );
};

