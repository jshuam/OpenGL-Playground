#include "Renderer.h"

void Renderer::prepare()
{
	glClear( GL_COLOR_BUFFER_BIT );
	glClearColor( 1, 0, 0, 1 );
}

void Renderer::render( const TexturedModel& textured_model )
{
	RawModel raw_model( textured_model.getRawModel() );
	glBindVertexArray( raw_model.getVaoId() );
	glEnableVertexAttribArray( 0 );
	glDrawElements( GL_TRIANGLES, raw_model.getVertexCount(), GL_UNSIGNED_INT, 0 );
	glDisableVertexAttribArray( 0 );
	glBindVertexArray( 0 );
}
