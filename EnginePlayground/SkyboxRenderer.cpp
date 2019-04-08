#include "DisplayManager.h"
#include "SkyboxRenderer.h"

#include <cmath>

SkyboxRenderer::SkyboxRenderer( Loader loader, glm::mat4 projection_matrix )
{
	cube = loader.loadToVAO( VERTICES, 3 );
	day_texture = loader.loadCubeMap( DAY_TEXTURE_FILES );
	night_texture = loader.loadCubeMap( NIGHT_TEXTURE_FILES );
	shader.start();
	shader.connectTextureUnits();
	shader.loadProjectionMatrix( projection_matrix );
	shader.stop();
}

void SkyboxRenderer::render( const Camera& camera, const glm::vec3& fog_colour, const bool& cell_shading )
{
	shader.start();
	shader.loadViewMatrix( camera, DisplayManager::getDeltaTime() );
	shader.loadFogColour( fog_colour.r, fog_colour.g, fog_colour.b );
	shader.loadProperties( cell_shading );
	glBindVertexArray( cube.getVaoId() );
	glEnableVertexAttribArray( 0 );
	bindTextures();
	glDrawArrays( GL_TRIANGLES, 0, cube.getVertexCount() );
	glDisableVertexAttribArray( 0 );
	glBindVertexArray( 0 );
	shader.stop();
}

void SkyboxRenderer::bindTextures()
{
	time += DisplayManager::getDeltaTime() * 1000;
	time = fmodf( time, 24000 );
	GLuint texture_1;
	GLuint texture_2;
	GLfloat blend_factor;

	if( time >= 0 && time < 5000 )
	{
		texture_1 = night_texture;
		texture_2 = night_texture;
		blend_factor = ( time - 0 ) / ( 5000 - 0 );
	}
	else if( time >= 5000 && time < 8000 )
	{
		texture_1 = night_texture;
		texture_2 = day_texture;
		blend_factor = ( time - 5000 ) / ( 8000 - 5000 );
	}
	else if( time >= 8000 && time < 21000 )
	{
		texture_1 = day_texture;
		texture_2 = day_texture;
		blend_factor = ( time - 8000 ) / ( 21000 - 8000 );
	}
	else
	{
		texture_1 = day_texture;
		texture_2 = night_texture;
		blend_factor = ( time - 21000 ) / ( 24000 - 21000 );
	}

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_CUBE_MAP, texture_1 );
	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_CUBE_MAP, texture_2 );
	shader.loadBlendFactor( blend_factor );
}
