#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
public:
	void start();
	void stop();
	void cleanUp();

protected:
	ShaderProgram() = default;
	virtual void bindAttributes() = 0;
	virtual void getAllUniformLocations() = 0;
	void bindAttribute( GLuint attribute, std::string variable_name );
	virtual ~ShaderProgram() = default;
	static GLuint loadShader( std::string filename, GLuint type );
	GLuint getUniformLocation( std::string uniform_name );
	void loadFloat( GLuint location, GLfloat value );
	void loadVector( GLuint location, glm::vec3 vector );
	void loadBool( GLuint location, GLboolean value );
	void loadMatrix( GLuint location, glm::mat4 matrix );

protected:
	GLuint program_id;
	GLuint vertex_shader_id;
	GLuint fragment_shader_id;
};

