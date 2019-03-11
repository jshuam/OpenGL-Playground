#pragma once
#include "ShaderProgram.h"
#include "glm/mat4x4.hpp"

class StaticShader : public ShaderProgram
{


public:
	StaticShader();
	~StaticShader() = default;

	void loadTransformationMatrix( const glm::mat4& matrix ) const;
	void loadProjectionMatrix( const glm::mat4& matrix ) const;
	void loadViewMatrix( const glm::mat4& matrix ) const;

protected:
	void bindAttributes() override;
	void getAllUniformLocations() override;

private:
	static constexpr const char* vertex_file = "vertex_shader.txt";
	static constexpr const char* fragment_file = "fragment_shader.txt";

	GLuint location_transform_mat;
	GLuint location_projection_mat;
	GLuint location_view_mat;
};
