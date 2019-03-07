#pragma once
#include "ShaderProgram.h"

class StaticShader : public ShaderProgram
{


public:
	StaticShader();
	~StaticShader() = default;

protected:
	void bindAttributes() override;

private:
	static constexpr const char* vertex_file = "vertex_shader.txt";
	static constexpr const char* fragment_file = "fragment_shader.txt";
};
