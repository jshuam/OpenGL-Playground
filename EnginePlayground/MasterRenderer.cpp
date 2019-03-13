#include "MasterRenderer.h"

MasterRenderer::MasterRenderer()
	:
	shader(),
	renderer( shader, createProjectionMatrix() ),
	entities()
{
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
}

void MasterRenderer::prepare() const
{
	glEnable( GL_DEPTH_TEST );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor( 0.25, 0.25, 0.25, 1 );
}

glm::mat4& MasterRenderer::createProjectionMatrix()
{
	float aspect_ratio = static_cast<float>( DisplayManager::getWidth() ) / static_cast<float>( DisplayManager::getHeight() );
	projection_matrix = glm::perspective( glm::radians( FOV ), aspect_ratio, NEAR_PLANE, FAR_PLANE );
	return projection_matrix;
}


void MasterRenderer::cleanUp()
{
	shader.cleanUp();
}

void MasterRenderer::render( const Light& light, const Camera& camera )
{
	prepare();
	shader.start();
	shader.loadLight( light );
	shader.loadViewMatrix( camera );
	renderer.render( entities );
	shader.stop();
	entities.clear();
}

void MasterRenderer::processEntity( const Entity& entity )
{
	const TexturedModel& entity_model = entity.getModel();
	auto batch = entities.find( entity_model );
	if( batch != entities.end())
	{
		batch->second.push_back( entity );
	}
	else
	{
		std::vector<Entity> new_batch;
		new_batch.push_back( entity );
		entities.emplace( entity_model, new_batch );
	}
}
