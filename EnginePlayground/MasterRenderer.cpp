#include "MasterRenderer.h"

MasterRenderer::MasterRenderer()
	:
	shader(),
	renderer( shader ),
	entities()
{}

void MasterRenderer::cleanUp()
{
	shader.cleanUp();
}

void MasterRenderer::render( const Light& light, const Camera& camera )
{
	renderer.prepare();
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
