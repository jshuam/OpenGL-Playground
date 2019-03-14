#include "Maths.h"
#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer( TerrainShader shader, glm::mat4 projection_matrix )
	:
	shader( shader )
{
	shader.start();
	shader.loadProjectionMatrix( projection_matrix );
	shader.stop();
}

void TerrainRenderer::render( const std::vector<Terrain>& terrains ) const
{
	for( auto& terrain : terrains )
	{
		prepareTerrain( terrain );
		loadModelMatrix( terrain );
		glDrawElements( GL_TRIANGLES, terrain.getModel().getVertexCount(), GL_UNSIGNED_INT, 0 );
		unbindTexturedModel();
	}
}

void TerrainRenderer::prepareTerrain( const Terrain& terrain ) const
{
	RawModel raw_model = terrain.getModel();
	glBindVertexArray( raw_model.getVaoId() );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glEnableVertexAttribArray( 2 );
	ModelTexture texture = terrain.getTexture();
	shader.loadShineVariables( texture.getShineDamper(), texture.getReflectivity() );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, texture.getID() );
}

void TerrainRenderer::unbindTexturedModel() const
{
	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
	glDisableVertexAttribArray( 2 );
	glBindVertexArray( 0 );
}

void TerrainRenderer::loadModelMatrix( const Terrain& terrain ) const
{
	glm::mat4 transformation_matrix = Maths::createTransformationMatrix( glm::vec3( terrain.getX(), 0, terrain.getZ() ), 0, 0, 0, 1 );
	shader.loadTransformationMatrix( transformation_matrix );
}
