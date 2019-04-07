#pragma once

#include "Camera.h"
#include "ShaderProgram.h"

#include <glad/glad.h>

class WaterShader : public ShaderProgram
{
public:
	WaterShader();
	~WaterShader() = default;

	void loadProjectionMatrix( const glm::mat4& projection_matrix );
	void loadViewMatrix( const Camera& camera );
	void loadModelMatrix( const glm::mat4& model_matrix );
	void loadMoveFactor( const GLfloat& factor );
	void connectTextureUnits();

protected:
	void bindAttributes() override;
	void getAllUniformLocations() override;

private:
	static constexpr const char* vertex_file = "water_vertex.txt";
	static constexpr const char* fragment_file = "water_fragment.txt";

	GLint location_model_matrix;
	GLint location_view_matrix;
	GLint location_projection_matrix;
	GLint location_reflection_texture;
	GLint location_refraction_texture;
	GLint location_dudv_map;
	GLint location_move_factor;
};

