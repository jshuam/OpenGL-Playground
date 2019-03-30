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
}

void WaterShader::loadModelMatrix( const glm::mat4& model_matrix )
{
	loadMatrix( location_model_matrix, model_matrix );
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
}
