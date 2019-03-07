#pragma once

#include <glad/glad.h>
#include "RawModel.h"

class Renderer
{
public:
	void prepare();
	void render(RawModel model);
};

