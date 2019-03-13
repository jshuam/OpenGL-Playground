#include "Renderer.h"

#include "DisplayManager.h"

Renderer::Renderer( StaticShader shader )
{
	this->shader = shader;
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	createProjectionMatrix();
	shader.start();
	shader.loadProjectionMatrix( projection_matrix );
	shader.stop();
}

void Renderer::prepare() const
{
	glEnable( GL_DEPTH_TEST );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor( 0.25, 0.25, 0.25, 1 );
}

void Renderer::render( const std::unordered_map<TexturedModel, std::vector<Entity>> entities )
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

void Renderer::createProjectionMatrix()
{
	float aspect_ratio = static_cast<float>( DisplayManager::getWidth() ) / static_cast<float>( DisplayManager::getHeight() );
	projection_matrix = glm::perspective( glm::radians( FOV ), aspect_ratio, NEAR_PLANE, FAR_PLANE );
}

void Renderer::prepareTexturedModel( const TexturedModel& model )
{
	RawModel raw_model( model.getRawModel() );
	glBindVertexArray( raw_model.getVaoId() );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glEnableVertexAttribArray( 2 );
	ModelTexture texture = model.getTexture();
	shader.loadShineVariables( texture.getShineDamper(), texture.getReflectivity() );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, model.getTexture().getID() );
}

void Renderer::unbindTexturedModel()
{
	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
	glDisableVertexAttribArray( 2 );
	glBindVertexArray( 0 );
}

void Renderer::prepareInstance( const Entity& entity )
{
	glm::mat4 transformation_matrix = Maths::createTransformationMatrix( entity.getPosition(), 
																		 entity.getRotX(), 
																		 entity.getRotY(), 
																		 entity.getRotZ(), 
																		 entity.getScale() );
	shader.loadTransformationMatrix( transformation_matrix );
}
