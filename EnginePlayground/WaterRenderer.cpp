#include "Maths.h"
#include "WaterRenderer.h"

WaterRenderer::WaterRenderer( Loader& loader, WaterShader& shader, const glm::mat4& projection_matrix )
	:
	shader(shader)
{
	shader.start();
	shader.loadProjectionMatrix( projection_matrix );
	shader.stop();
	setUpVAO( loader );
}

void WaterRenderer::render( const std::vector<WaterTile>& water, const Camera& camera )
{
	prepareRender( camera );

	for( auto& tile : water )
	{
		glm::mat4 model_matrix = Maths::createTransformationMatrix( glm::vec3( tile.getX(), tile.getHeight(), tile.getZ() ), 0, 0, 0, WaterTile::TILE_SIZE );
		shader.loadModelMatrix( model_matrix );
		glDrawArrays( GL_TRIANGLES, 0, quad.getVertexCount() );
	}
	unbind();
}

void WaterRenderer::prepareRender( const Camera& camera )
{
	shader.start();
	shader.loadViewMatrix( camera );
	glBindVertexArray( quad.getVaoId() );
}

void WaterRenderer::unbind()
{
	glDisableVertexAttribArray( 0 );
	glBindVertexArray( 0 );
	shader.stop();
}

void WaterRenderer::setUpVAO( Loader& loader )
{
	std::vector<GLfloat> vertices = { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };
	quad = loader.loadToVAO( vertices, 2 );
}
