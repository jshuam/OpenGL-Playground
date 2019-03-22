#include "SkyboxRenderer.h"

SkyboxRenderer::SkyboxRenderer( Loader loader, glm::mat4 projection_matrix )
{
	cube = loader.loadToVAO( VERTICES, 3 );
	texture = loader.loadCubeMap( TEXTURE_FILES );
	shader.start();
	shader.loadProjectionMatrix( projection_matrix );
	shader.stop();
}

void SkyboxRenderer::render( const Camera& camera )
{
	shader.start();
	shader.loadViewMatrix( camera );
	glBindVertexArray( cube.getVaoId() );
	glEnableVertexAttribArray( 0 );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_CUBE_MAP, texture );
	glDrawArrays( GL_TRIANGLES, 0, cube.getVertexCount() );
	glDisableVertexAttribArray( 0 );
	glBindVertexArray( 0 );
	shader.stop();
}
