#include "Renderer.h"

void Renderer::prepare()
{
	glClear( GL_COLOR_BUFFER_BIT );
	glClearColor( 0.25, 0.25, 0.25, 1 );
}

void Renderer::render( const TexturedModel& textured_model )
{
	RawModel raw_model( textured_model.getRawModel() );
	glBindVertexArray( raw_model.getVaoId() );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, textured_model.getTexture().getID() );
	glDrawElements( GL_TRIANGLES, raw_model.getVertexCount(), GL_UNSIGNED_INT, 0 );
	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
	glBindVertexArray( 0 );
}
