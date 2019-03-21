#pragma once

#include "ShaderProgram.h"

class SkyboxShader : public ShaderProgram
{
public:
	SkyboxShader();
	~SkyboxShader() = default;

	void loadProjectionMatrix( const glm::mat4& matrix ) const;
	void loadViewMatrix( const Camera& camera ) const;

protected:
	void bindAttributes() override;
	void getAllUniformLocations() override;

private:
	static constexpr const char* vertex_file = "skybox_vertex_shader.txt";
	static constexpr const char* fragment_file = "skybox_fragment_shader.txt";

	GLuint location_projection_mat;
	GLuint location_view_mat;
};

