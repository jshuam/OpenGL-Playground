#include "MasterRenderer.h"

MasterRenderer::MasterRenderer()
{
	createProjectionMatrix();
	renderer = EntityRenderer( shader, projection_matrix );
	terrain_renderer = TerrainRenderer( terrain_shader, projection_matrix );
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
}

void MasterRenderer::prepare() const
{
	glEnable( GL_DEPTH_TEST );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor( (148.0f / 255.0f), (183.0f / 255.0f), (239.0f / 255.0f), 1 );
}

void MasterRenderer::createProjectionMatrix()
{
	float aspect_ratio = static_cast<float>( DisplayManager::getWidth() ) / static_cast<float>( DisplayManager::getHeight() );
	projection_matrix = glm::perspective( glm::radians( FOV ), aspect_ratio, NEAR_PLANE, FAR_PLANE );
}


void MasterRenderer::cleanUp()
{
	shader.cleanUp();
	terrain_shader.cleanUp();
}

void MasterRenderer::render( const Light& light, const Camera& camera )
{
	prepare();
	shader.start();
	shader.loadLight( light );
	shader.loadViewMatrix( camera );
	renderer.render( entities );
	shader.stop();
	terrain_shader.start();
	terrain_shader.loadLight( light );
	terrain_shader.loadViewMatrix( camera );
	terrain_renderer.render( terrains );
	terrain_shader.stop();
	terrains.clear();
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

void MasterRenderer::processTerrain( const Terrain& terrain )
{
	terrains.push_back( terrain );
}