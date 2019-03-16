#include "DisplayManager.h"
#include "EntityRenderer.h"
#include "MasterRenderer.h"

EntityRenderer::EntityRenderer( StaticShader shader, glm::mat4 projection_matrix )
{
	this->shader = shader;
	shader.start();
	shader.loadProjectionMatrix( projection_matrix );
	shader.stop();
}

void EntityRenderer::render( const std::unordered_map<TexturedModel, std::vector<Entity>> entities )
{
	for( auto& model : entities )
	{
		const TexturedModel& textured_model = model.first;
		prepareTexturedModel( textured_model );
		std::vector<Entity> batch = model.second;
		for( auto& entity : batch )
		{
			prepareInstance( entity );
			glDrawElements( GL_TRIANGLES, textured_model.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0 );
		}
		unbindTexturedModel();
	}
}


void EntityRenderer::prepareTexturedModel( const TexturedModel& model )
{
	RawModel raw_model( model.getRawModel() );
	glBindVertexArray( raw_model.getVaoId() );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glEnableVertexAttribArray( 2 );
	ModelTexture texture = model.getTexture();
	if( texture.hasTransparency() )
	{
		MasterRenderer::disableCulling();
	}
	shader.loadFakeLighting( texture.hasFakeLighting() );
	shader.loadShineVariables( texture.getShineDamper(), texture.getReflectivity() );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, model.getTexture().getID() );
}

void EntityRenderer::unbindTexturedModel()
{
	MasterRenderer::enableCulling();
	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
	glDisableVertexAttribArray( 2 );
	glBindVertexArray( 0 );
}

void EntityRenderer::prepareInstance( const Entity& entity )
{
	glm::mat4 transformation_matrix = Maths::createTransformationMatrix( entity.getPosition(), 
																		 entity.getRotX(), 
																		 entity.getRotY(), 
																		 entity.getRotZ(), 
																		 entity.getScale() );
	shader.loadTransformationMatrix( transformation_matrix );
}
