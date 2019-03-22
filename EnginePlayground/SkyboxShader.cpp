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

void SkyboxShader::loadViewMatrix( const Camera& camera, const GLfloat& dt )
{
	glm::mat4 view_matrix = Maths::createViewMatrix( camera );
	view_matrix[3][0] = 0;
	view_matrix[3][1] = 0;
	view_matrix[3][2] = 0;
	rotation += ROTATE_SPEED * dt;
	view_matrix = glm::rotate( view_matrix, glm::radians( rotation ), glm::vec3( 0, 1, 0 ) );
	loadMatrix( location_view_mat, view_matrix );
}

void SkyboxShader::loadFogColour( GLfloat r, GLfloat g, GLfloat b ) const
{
	loadVector( location_fog_colour, glm::vec3( r, g, b ) );
}

void SkyboxShader::loadBlendFactor( GLfloat blend_factor ) const
{
	loadFloat( location_blend_factor, blend_factor );
}

void SkyboxShader::connectTextureUnits()
{
	loadInt( location_cube_map_day, 0 );
	loadInt( location_cube_map_night, 1 );
}

void SkyboxShader::bindAttributes()
{
	bindAttribute( 0, "position" );
}

void SkyboxShader::getAllUniformLocations()
{
	location_projection_mat = getUniformLocation( "projection_matrix" );
	location_view_mat = getUniformLocation( "view_matrix" );
	location_fog_colour = getUniformLocation( "fog_colour" );
	location_cube_map_day = getUniformLocation( "cube_map_day" );
	location_cube_map_night = getUniformLocation( "cube_map_night" );
	location_blend_factor = getUniformLocation( "blend_factor" );
}
