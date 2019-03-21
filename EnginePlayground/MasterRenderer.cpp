#include "MasterRenderer.h"

MasterRenderer::MasterRenderer( GLuint num_lights )
{
	createProjectionMatrix();
	renderer = EntityRenderer( &shader, projection_matrix, num_lights );
	terrain_renderer = TerrainRenderer( &terrain_shader, projection_matrix, num_lights );
	enableCulling();
}

void MasterRenderer::prepare() const
{
	glEnable( GL_DEPTH_TEST );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor( RED, GREEN, BLUE, 1 );
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

void MasterRenderer::disableCulling()
{
	glDisable( GL_CULL_FACE );
}

void MasterRenderer::enableCulling()
{
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
}

void MasterRenderer::render( const std::vector<Light>& lights, const Camera& camera )
{
	prepare();
	shader.start();
	shader.loadSkyColour( RED, GREEN, BLUE );
	shader.loadLights( lights );
	shader.loadViewMatrix( camera );
	renderer.render( entities );
	shader.stop();
	terrain_shader.start();
	terrain_shader.loadSkyColour( RED, GREEN, BLUE );
	terrain_shader.loadLights( lights );
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
	if( batch != entities.end() )
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
