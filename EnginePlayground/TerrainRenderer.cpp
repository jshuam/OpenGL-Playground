#include "Maths.h"
#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer( TerrainShader* shader, glm::mat4 projection_matrix, GLuint num_lights )
	:
	shader( shader )
{
	shader->start();
	shader->loadProjectionMatrix( projection_matrix );
	shader->loadNumLights( num_lights );
	shader->connectTextureUnits();
	shader->stop();
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
	bindTextures( terrain );
	shader->loadShineVariables( 1, 0 );
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
	shader->loadTransformationMatrix( transformation_matrix );
}

void TerrainRenderer::bindTextures( const Terrain& terrain ) const
{
	TerrainTexturePack texture_pack = terrain.getTexturePack();

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, texture_pack.getBackgroundTexture().getTextureId() );

	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, texture_pack.getRTexture().getTextureId() );

	glActiveTexture( GL_TEXTURE2 );
	glBindTexture( GL_TEXTURE_2D, texture_pack.getGTexture().getTextureId() );

	glActiveTexture( GL_TEXTURE3 );
	glBindTexture( GL_TEXTURE_2D, texture_pack.getBTexture().getTextureId() );

	glActiveTexture( GL_TEXTURE4 );
	glBindTexture( GL_TEXTURE_2D, terrain.getBlendMap().getTextureId() );

}
