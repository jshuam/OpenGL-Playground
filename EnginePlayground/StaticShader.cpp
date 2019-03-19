#include "StaticShader.h"
#include "Maths.h"

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
	getAllUniformLocations();
}

void StaticShader::loadTransformationMatrix( const glm::mat4& matrix ) const
{
	loadMatrix( location_transform_mat, matrix );
}

void StaticShader::loadProjectionMatrix( const glm::mat4& matrix ) const
{
	loadMatrix( location_projection_mat, matrix );
}

void StaticShader::loadViewMatrix( const Camera& camera ) const
{
	glm::mat4 view_matrix = Maths::createViewMatrix( camera );
	loadMatrix( location_view_mat, view_matrix );
}

void StaticShader::loadLight( const Light& light ) const
{
	loadVector( location_light_position, light.getPosition() );
	loadVector( location_light_colour, light.getColour() );
}

void StaticShader::loadShineVariables( const GLfloat& damper, const GLfloat& reflectivity ) const
{
	loadFloat( location_shine_damper, damper );
	loadFloat( location_reflectivity, reflectivity );
}

void StaticShader::loadFakeLighting( const GLboolean& use_fake_lighting ) const
{
	loadBool( location_use_fake_lighting, use_fake_lighting );
}

void StaticShader::loadSkyColour( const GLfloat& r, const GLfloat& g, const GLfloat& b ) const
{
	loadVector( location_sky_colour, glm::vec3( r, g, b ) );
}

void StaticShader::loadNumRows( const GLuint& num_rows ) const
{
	loadFloat( location_num_rows, num_rows );
}

void StaticShader::loadOffset( const GLfloat& x, const GLfloat& y ) const
{
	loadVector2D( location_offset, glm::vec2( x, y ) );
}

void StaticShader::bindAttributes()
{
	bindAttribute( 0, "position" );
	bindAttribute( 1, "texture_coords" );
	bindAttribute( 2, "normal" );
}

void StaticShader::getAllUniformLocations()
{
	location_transform_mat = getUniformLocation( "transformation_matrix" );
	location_projection_mat = getUniformLocation( "projection_matrix" );
	location_view_mat = getUniformLocation( "view_matrix" );
	location_light_position = getUniformLocation( "light_position" );
	location_light_colour = getUniformLocation( "light_colour" );
	location_shine_damper = getUniformLocation( "shine_damper" );
	location_reflectivity = getUniformLocation( "reflectivity" );
	location_use_fake_lighting = getUniformLocation( "use_fake_lighting" );
	location_sky_colour = getUniformLocation( "sky_colour" );
	location_num_rows = getUniformLocation( "num_rows" );
	location_offset = getUniformLocation( "offset" );
}
