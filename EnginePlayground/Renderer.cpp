#include "Renderer.h"

void Renderer::prepare()
{
	glClear( GL_COLOR_BUFFER_BIT );
	glClearColor( 1, 0, 0, 1 );
}

void Renderer::render( const RawModel& model )
{
	glBindVertexArray( model.getVaoId() );
	glEnableVertexAttribArray( 0 );
	glDrawElements( GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0 );
	glDisableVertexAttribArray( 0 );
	glBindVertexArray( 0 );
}
