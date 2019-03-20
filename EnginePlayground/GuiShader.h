#pragma once

#include "ShaderProgram.h"

class GuiShader : public ShaderProgram
{

public:
	GuiShader();
	~GuiShader() = default;

	void loadTransformationMatrix( const glm::mat4& matrix ) const;

protected:
	void bindAttributes() override;
	void getAllUniformLocations() override;

private:
	static constexpr const char* vertex_file = "gui_vertex_shader.txt";
	static constexpr const char* fragment_file = "gui_fragment_shader.txt";

	GLuint location_transform_mat;
};

