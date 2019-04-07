#include "Maths.h"
#include "WaterShader.h"

WaterShader::WaterShader() : ShaderProgram()
{
	init( vertex_file, fragment_file );
}

void WaterShader::loadProjectionMatrix( const glm::mat4& projection_matrix )
{
	loadMatrix( location_projection_matrix, projection_matrix );
}

void WaterShader::loadViewMatrix( const Camera& camera )
{
	loadMatrix( location_view_matrix, Maths::createViewMatrix( camera ) );
	loadVector( location_camera_position, camera.getPosition() );
}

void WaterShader::loadModelMatrix( const glm::mat4& model_matrix )
{
	loadMatrix( location_model_matrix, model_matrix );
}

void WaterShader::loadMoveFactor( const GLfloat& factor )
{
	loadFloat( location_move_factor, factor );
}

void WaterShader::loadLight( const Light& light )
{
	loadVector( location_light_colour, light.getColour() );
	loadVector( location_light_position, light.getPosition() );
}

void WaterShader::connectTextureUnits()
{
	loadInt( location_reflection_texture, 0 );
	loadInt( location_refraction_texture, 1 );
	loadInt( location_dudv_map, 2 );
	loadInt( location_normal_map, 3 );
}

void WaterShader::bindAttributes()
{
	bindAttribute( 0, "position" );
}

void WaterShader::getAllUniformLocations()
{
	location_projection_matrix = getUniformLocation( "projection_matrix" );
	location_view_matrix = getUniformLocation( "view_matrix" );
	location_model_matrix = getUniformLocation( "model_matrix" );
	location_reflection_texture = getUniformLocation( "reflection_texture" );
	location_refraction_texture = getUniformLocation( "refraction_texture" );
	location_dudv_map = getUniformLocation( "dudv_map" );
	location_move_factor = getUniformLocation( "move_factor" );
	location_camera_position = getUniformLocation( "camera_position" );
	location_normal_map = getUniformLocation( "normal_map" );
	location_light_colour = getUniformLocation( "light_colour" );
	location_light_position = getUniformLocation( "light_position" );
}
