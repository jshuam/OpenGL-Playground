#pragma once

#include "Camera.h"
#include "Light.h"
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
	void loadLight( const Light& light );
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
	GLint location_camera_position;
	GLint location_normal_map;
	GLint location_light_colour;
	GLint location_light_position;
	GLint location_depth_map;
};

