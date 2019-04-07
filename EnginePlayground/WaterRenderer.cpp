#include "Maths.h"
#include "WaterRenderer.h"

WaterRenderer::WaterRenderer( Loader& loader, WaterShader& shader, const glm::mat4& projection_matrix, WaterFrameBuffer& water_fbos )
	:
	shader( shader ),
	water_fbos( water_fbos )
{
	dudv_texture = loader.loadTexture( dudv_map );
	normal_map_texture = loader.loadTexture( normal_map );
	shader.start();
	shader.connectTextureUnits();
	shader.loadProjectionMatrix( projection_matrix );
	shader.stop();
	setUpVAO( loader );
}

void WaterRenderer::render( const std::vector<WaterTile>& water, const Camera& camera, const Light& sun )
{
	prepareRender( camera, sun );

	for( auto& tile : water )
	{
		glm::mat4 model_matrix = Maths::createTransformationMatrix( glm::vec3( tile.getX(), tile.getHeight(), tile.getZ() ), 0, 0, 0, WaterTile::TILE_SIZE );
		shader.loadModelMatrix( model_matrix );
		glDrawArrays( GL_TRIANGLES, 0, quad.getVertexCount() );
	}
	unbind();
}

void WaterRenderer::prepareRender( const Camera& camera, const Light& sun )
{
	shader.start();
	shader.loadViewMatrix( camera );
	move_factor += wave_speed * DisplayManager::getDeltaTime();
	move_factor = fmod( move_factor, 1 );
	shader.loadMoveFactor( move_factor );
	shader.loadLight( sun );
	glBindVertexArray( quad.getVaoId() );
	glEnableVertexAttribArray( 0 );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, water_fbos.getReflectionTexture() );
	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, water_fbos.getRefractionTexture() );
	glActiveTexture( GL_TEXTURE2 );
	glBindTexture( GL_TEXTURE_2D, dudv_texture );
	glActiveTexture( GL_TEXTURE3 );
	glBindTexture( GL_TEXTURE_2D, normal_map_texture );
	glActiveTexture( GL_TEXTURE4 );
	glBindTexture( GL_TEXTURE_2D, water_fbos.getRefractionDepthTexture() );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void WaterRenderer::unbind()
{
	glDisable( GL_BLEND );
	glDisableVertexAttribArray( 0 );
	glBindVertexArray( 0 );
	shader.stop();
}

void WaterRenderer::setUpVAO( Loader& loader )
{
	std::vector<GLfloat> vertices = { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };
	quad = loader.loadToVAO( vertices, 2 );
}
