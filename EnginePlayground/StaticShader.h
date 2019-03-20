#pragma once
#include "ShaderProgram.h"
#include "glm/mat4x4.hpp"
#include "Camera.h"
#include "Light.h"

class StaticShader : public ShaderProgram
{

public:
	StaticShader();
	~StaticShader() = default;

	void loadTransformationMatrix( const glm::mat4& matrix ) const;
	void loadProjectionMatrix( const glm::mat4& matrix ) const;
	void loadViewMatrix( const Camera& camera ) const;
	void loadLights( const std::vector<Light>& lights );
	void loadShineVariables( const GLfloat& damper, const GLfloat& reflectivity ) const;
	void loadFakeLighting( const GLboolean& use_fake_lighting ) const;
	void loadSkyColour( const GLfloat& r, const GLfloat& g, const GLfloat& b ) const;
	void loadNumRows( const GLuint& num_rows ) const;
	void loadOffset( const GLfloat& x, const GLfloat& y ) const;

protected:
	void bindAttributes() override;
	void getAllUniformLocations() override;

private:
	static constexpr const char* vertex_file = "vertex_shader.txt";
	static constexpr const char* fragment_file = "fragment_shader.txt";

	GLuint location_transform_mat;
	GLuint location_projection_mat;
	GLuint location_view_mat;
	GLuint location_shine_damper;
	GLuint location_reflectivity;
	GLuint location_use_fake_lighting;
	GLuint location_sky_colour;
	GLuint location_num_rows;
	GLuint location_offset;
	GLuint location_max_lights;
	std::vector<GLuint> location_light_position;
	std::vector<GLuint> location_light_colour;
};
