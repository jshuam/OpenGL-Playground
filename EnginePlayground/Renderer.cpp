#include "Renderer.h"

void Renderer::prepare()
{
	glClearColor( 1, 0, 0, 1 );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Renderer::render(RawModel model)
{
	glBindVertexArray( model.getVaoId() );
	glEnableVertexAttribArray( 0 );
	glDrawArrays( GL_TRIANGLES, 0, model.getVertexCount() );
	glDisableVertexAttribArray( 0 );
	glBindVertexArray( 0 );
}
