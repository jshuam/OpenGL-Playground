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

void TerrainShader::loadNumLights( GLuint num_lights )
{
	loadFloat( location_max_lights, num_lights );
	location_light_position.reserve( num_lights );
	location_light_colour.reserve( num_lights );
	location_attenuation.resize( num_lights );
	for( GLuint i = 0; i < num_lights; i++ )
	{
		location_light_position.push_back( getUniformLocation( "light_position[" + std::to_string( i ) + "]" ) );
		location_light_colour.push_back( getUniformLocation( "light_colour[" + std::to_string( i ) + "]" ) );
		location_attenuation[i] = getUniformLocation( "attenuation[" + std::to_string( i ) + "]" );
	}
}

void TerrainShader::loadLights( const std::vector<Light>& lights )
{
	for( GLuint i = 0; i < lights.size(); i++ )
	{
		loadVector( location_light_position[i], lights[i].getPosition() );
		loadVector( location_light_colour[i], lights[i].getColour() );
		loadVector( location_attenuation[i], lights[i].getAttenuation() );
	}
}

void TerrainShader::loadShineVariables( const GLfloat& damper, const GLfloat& reflectivity ) const
{
	loadFloat( location_shine_damper, damper );
	loadFloat( location_reflectivity, reflectivity );
}

void TerrainShader::loadSkyColour( const GLfloat& r, const GLfloat& g, const GLfloat& b ) const
{
	loadVector( location_sky_colour, glm::vec3( r, g, b ) );
}

void TerrainShader::connectTextureUnits()
{
	loadInt( location_background_texture, 0 );
	loadInt( location_r_texture, 1 );
	loadInt( location_g_texture, 2 );
	loadInt( location_b_texture, 3 );
	loadInt( location_blend_map, 4 );
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
	location_shine_damper = getUniformLocation( "shine_damper" );
	location_reflectivity = getUniformLocation( "reflectivity" );
	location_sky_colour = getUniformLocation( "sky_colour" );
	location_background_texture = getUniformLocation( "background_texture" );
	location_r_texture = getUniformLocation( "r_texture" );
	location_g_texture = getUniformLocation( "g_texture" );
	location_b_texture = getUniformLocation( "b_texture" );
	location_blend_map = getUniformLocation( "blend_map" );
	location_max_lights = getUniformLocation( "max_lights" );
}
