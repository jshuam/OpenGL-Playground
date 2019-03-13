#pragma once

#include "Camera.h"
#include "Light.h"
#include "ShaderProgram.h"

class TerrainShader : public ShaderProgram
{

public:
	TerrainShader();
	~TerrainShader() = default;

	void loadTransformationMatrix( const glm::mat4& matrix ) const;
	void loadProjectionMatrix( const glm::mat4& matrix ) const;
	void loadViewMatrix( const Camera& camera ) const;
	void loadLight( const Light& light ) const;
	void loadShineVariables( const GLfloat& damper, const GLfloat& reflectivity ) const;

protected:
	void bindAttributes() override;
	void getAllUniformLocations() override;

private:
	static constexpr const char* vertex_file = "terrain_vertex_shader.txt";
	static constexpr const char* fragment_file = "terrain_fragment_shader.txt";

	GLuint location_transform_mat;
	GLuint location_projection_mat;
	GLuint location_view_mat;
	GLuint location_light_position;
	GLuint location_light_colour;
	GLuint location_shine_damper;
	GLuint location_reflectivity;
};

