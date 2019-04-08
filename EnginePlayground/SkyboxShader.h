#pragma once

#include "ShaderProgram.h"

class SkyboxShader : public ShaderProgram
{
public:
	SkyboxShader();
	~SkyboxShader() = default;

	void loadProjectionMatrix( const glm::mat4& matrix ) const;
	void loadViewMatrix( const Camera& camera, const GLfloat& dt );
	void loadFogColour( GLfloat r, GLfloat g, GLfloat b ) const;
	void loadBlendFactor( GLfloat blend_factor ) const;
	void loadProperties( const bool& cell_shading ) const;
	void connectTextureUnits();

protected:
	void bindAttributes() override;
	void getAllUniformLocations() override;

private:
	static constexpr const char* vertex_file = "skybox_vertex_shader.txt";
	static constexpr const char* fragment_file = "skybox_fragment_shader.txt";

	static constexpr const GLfloat ROTATE_SPEED = 1.0f;

	GLfloat rotation = 0;

	GLuint location_projection_mat;
	GLuint location_view_mat;
	GLuint location_fog_colour;
	GLuint location_cube_map_day;
	GLuint location_cube_map_night;
	GLuint location_blend_factor;
	GLuint location_cell_shading;
};

