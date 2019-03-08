#include "StaticShader.h"

StaticShader::StaticShader() : ShaderProgram()
{
	vertex_shader_id = loadShader( vertex_file, GL_VERTEX_SHADER );
	fragment_shader_id = loadShader( fragment_file, GL_FRAGMENT_SHADER );
	program_id = glCreateProgram();
	glAttachShader( program_id, vertex_shader_id );
	glAttachShader( program_id, fragment_shader_id );
	bindAttributes();
	glLinkProgram( program_id );
	glValidateProgram( program_id );
}

void StaticShader::bindAttributes()
{
	bindAttribute( 0, "position" );
	bindAttribute( 1, "texture_coords" );
}
