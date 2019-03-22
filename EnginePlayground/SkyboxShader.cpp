#include "Maths.h"
#include "SkyboxShader.h"

SkyboxShader::SkyboxShader() : ShaderProgram()
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

void SkyboxShader::loadProjectionMatrix( const glm::mat4& matrix ) const
{
	loadMatrix( location_projection_mat, matrix );
}

void SkyboxShader::loadViewMatrix( const Camera& camera ) const
{
	glm::mat4 view_matrix = Maths::createViewMatrix( camera );
	view_matrix[3][0] = 0;
	view_matrix[3][1] = 0;
	view_matrix[3][2] = 0;
	loadMatrix( location_view_mat, view_matrix );
}

void SkyboxShader::bindAttributes()
{
	bindAttribute( 0, "position" );
}

void SkyboxShader::getAllUniformLocations()
{
	location_projection_mat = getUniformLocation( "projection_matrix" );
	location_view_mat = getUniformLocation( "view_matrix" );
}
