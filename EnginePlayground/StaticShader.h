#pragma once
#include "ShaderProgram.h"
#include "glm/mat4x4.hpp"

class StaticShader : public ShaderProgram
{


public:
	StaticShader();
	~StaticShader() = default;

	void loadTransformationMatrix( glm::mat4 matrix );

protected:
	void bindAttributes() override;
	void getAllUniformLocations() override;

private:
	static constexpr const char* vertex_file = "vertex_shader.txt";
	static constexpr const char* fragment_file = "fragment_shader.txt";

	GLuint location_transform_mat;
};
