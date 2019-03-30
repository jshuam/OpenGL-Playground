#include "GuiShader.h"

GuiShader::GuiShader() : ShaderProgram()
{
	init( vertex_file, fragment_file );
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
