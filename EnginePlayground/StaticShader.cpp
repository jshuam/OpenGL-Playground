#include "StaticShader.h"

StaticShader::StaticShader() : ShaderProgram( vertex_file, fragment_file )
{}

void StaticShader::bindAttributes()
{
	bindAttribute( 0, "position" );
}
