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
	void start() const;
	void stop() const;
	void cleanUp();

protected:
	ShaderProgram() = default;
	void init( const char* vertex_file, const char* fragment_file );
	virtual void bindAttributes() = 0;
	virtual void getAllUniformLocations() = 0;
	void bindAttribute( GLuint attribute, std::string variable_name );
	virtual ~ShaderProgram() = default;
	static GLuint loadShader( std::string filename, GLuint type );
	GLuint getUniformLocation( std::string uniform_name );
	void loadFloat( const GLuint& location, const GLfloat& value ) const;
	void loadVector( const GLuint& location, const glm::vec2& vector ) const;
	void loadVector( const GLuint& location, const glm::vec3& vector ) const;
	void loadVector( const GLuint& location, const glm::vec4& vector ) const;
	void loadBool( const GLuint& location, const GLboolean& value ) const;
	void loadMatrix( const GLuint& location, const glm::mat4& matrix ) const;
	void loadInt( const GLuint& location, const GLuint& value ) const;

protected:
	GLuint program_id;
	GLuint vertex_shader_id;
	GLuint fragment_shader_id;
};

