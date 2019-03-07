#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class ShaderProgram
{
public:
	void start();
	void stop();
	void cleanUp();

protected:
	ShaderProgram( std::string vertex_filename, std::string fragment_filename );
	virtual void bindAttributes() = 0;
	void bindAttribute( GLuint attribute, std::string variable_name );
	virtual ~ShaderProgram() = default;

private:
	static GLuint loadShader( std::string filename, GLuint type );

private:
	GLuint program_id;
	GLuint vertex_shader_id;
	GLuint fragment_shader_id;
};

