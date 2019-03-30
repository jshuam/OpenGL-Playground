#pragma once

#include "ShaderProgram.h"

#include <glad/glad.h>

class WaterShader : public ShaderProgram
{
public:
	WaterShader() = default;
	~WaterShader() = default;

private:
	static constexpr const char* vertex_file = "water_vertex.txt";
	static constexpr const char* fragment_file = "water_fragment.txt";

	GLint location_model_matrix;
	GLint location_view_matrix;
	GLint location_projection_matrix;
};

