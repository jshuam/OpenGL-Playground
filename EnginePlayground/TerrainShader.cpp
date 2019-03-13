#include "TerrainShader.h"
#include "Maths.h"

TerrainShader::TerrainShader() : ShaderProgram()
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

void TerrainShader::loadTransformationMatrix( const glm::mat4& matrix ) const
{
	loadMatrix( location_transform_mat, matrix );
}

void TerrainShader::loadProjectionMatrix( const glm::mat4& matrix ) const
{
	loadMatrix( location_projection_mat, matrix );
}

void TerrainShader::loadViewMatrix( const Camera& camera ) const
{
	glm::mat4 view_matrix = Maths::createViewMatrix( camera );
	loadMatrix( location_view_mat, view_matrix );
}

void TerrainShader::loadLight( const Light& light ) const
{
	loadVector( location_light_position, light.getPosition() );
	loadVector( location_light_colour, light.getColour() );
}

void TerrainShader::loadShineVariables( const GLfloat& damper, const GLfloat& reflectivity ) const
{
	loadFloat( location_shine_damper, damper );
	loadFloat( location_reflectivity, reflectivity );
}

void TerrainShader::bindAttributes()
{
	bindAttribute( 0, "position" );
	bindAttribute( 1, "texture_coords" );
	bindAttribute( 2, "normal" );
}

void TerrainShader::getAllUniformLocations()
{
	location_transform_mat = getUniformLocation( "transformation_matrix" );
	location_projection_mat = getUniformLocation( "projection_matrix" );
	location_view_mat = getUniformLocation( "view_matrix" );
	location_light_position = getUniformLocation( "light_position" );
	location_light_colour = getUniformLocation( "light_colour" );
	location_shine_damper = getUniformLocation( "shine_damper" );
	location_reflectivity = getUniformLocation( "reflectivity" );
}
