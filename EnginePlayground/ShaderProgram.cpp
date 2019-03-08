#include "ShaderProgram.h"



void ShaderProgram::start()
{
	glUseProgram( program_id );
}

void ShaderProgram::stop()
{
	glUseProgram( 0 );
}

void ShaderProgram::cleanUp()
{
	stop();
	glDetachShader( program_id, vertex_shader_id );
	glDetachShader( program_id, fragment_shader_id );
	glDeleteShader( vertex_shader_id );
	glDeleteShader( fragment_shader_id );
	glDeleteProgram( program_id );
}

void ShaderProgram::bindAttribute( GLuint attribute, std::string variable_name )
{
	glBindAttribLocation( program_id, attribute, variable_name.c_str() );
}

GLuint ShaderProgram::loadShader( std::string filename, GLuint type )
{
	try
	{
		std::ifstream in( filename );
		std::stringstream shader_source_stream;
		std::string shader_source;
		shader_source_stream << in.rdbuf();
		shader_source = shader_source_stream.str();
		GLuint shader_id = glCreateShader( type );
		auto shader_source_c_str = shader_source.c_str();
		glShaderSource( shader_id, 1, &shader_source_c_str, NULL );
		glCompileShader( shader_id );

		GLint shader_compile_status = GL_FALSE;
		glGetShaderiv( shader_id, GL_COMPILE_STATUS, &shader_compile_status );

		if( shader_compile_status == GL_FALSE )
		{
			GLint max_length = 0;
			glGetShaderiv( shader_id, GL_INFO_LOG_LENGTH, &max_length );
			std::string error_log;
			error_log.reserve( max_length );
			glGetShaderInfoLog( shader_id, max_length, NULL, &error_log[0] );
			std::cout << error_log << std::endl;
			std::cout << "Could not compile shader." << std::endl;
			exit( -1 );
		}

		in.close();
		return shader_id;
	}
	catch( std::exception& e )
	{
		std::cout << e.what() << std::endl;
	}
}

GLuint ShaderProgram::getUniformLocation( std::string uniform_name )
{
	return glGetUniformLocation( program_id, uniform_name.c_str() );
}

void ShaderProgram::loadFloat( GLuint location, GLfloat value )
{
	glUniform1f( location, value );
}

void ShaderProgram::loadVector( GLuint location, glm::vec3 vector )
{
	glUniform3f( location, vector.x, vector.y, vector.z );
}

void ShaderProgram::loadBool( GLuint location, GLboolean value )
{
	glUniform1f( location, static_cast<GLfloat>( value ? 1 : 0 ) );
}

void ShaderProgram::loadMatrix( GLuint location, glm::mat4 matrix )
{
	glUniformMatrix4fv( location, 1, GL_FALSE, glm::value_ptr( matrix ) );
}
