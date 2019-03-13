#pragma once

#include "TerrainShader.h"

class TerrainRenderer
{
public:
	TerrainRenderer( TerrainShader shader, glm::mat4 projection_matrix );
	~TerrainRenderer() = default;

private:
	TerrainShader shader;
};

