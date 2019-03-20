#include "GuiShader.h"

GuiShader::GuiShader() : ShaderProgram()
{
	vertex_shader_id = loadShader( vertex_file, GL_VERTEX_SHADER );
	fragment_shader_id = loadShader( fragment_file, GL_FRAGMENT_SHADER );
	program_id = glCreateProgram();
	glAttachShader( program_id, vertex_shader_id );
	glAttachShader( program_id, fragment_shader_id );
	bindAttributes();
	glLinkProgram( program_id );
	glValidateProgram( program_id );
	getAllUniformLocations();
}

void GuiShader::loadTransformationMatrix( const glm::mat4& matrix ) const
{
	loadMatrix( location_transform_mat, matrix );
}

void GuiShader::bindAttributes()
{
	bindAttribute( 0, "position" );
}

void GuiShader::getAllUniformLocations()
{
	location_transform_mat = getUniformLocation( "transformation_matrix" );
}
