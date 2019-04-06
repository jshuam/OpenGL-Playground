#include "MasterRenderer.h"

MasterRenderer::MasterRenderer( Loader loader, GLuint num_lights )
{
	createProjectionMatrix();
	renderer = EntityRenderer( &shader, projection_matrix, num_lights );
	terrain_renderer = TerrainRenderer( &terrain_shader, projection_matrix, num_lights );
	skybox_renderer = SkyboxRenderer( loader, projection_matrix );
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
	frustum.setCamInternals( FOV, aspect_ratio, NEAR_PLANE, FAR_PLANE );
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

void MasterRenderer::render( const std::vector<std::shared_ptr<Light>>& lights, const Camera& camera, const glm::vec4& clip_plane )
{
	prepare();
	shader.start();
	shader.loadClipPlane( clip_plane );
	shader.loadSkyColour( RED, GREEN, BLUE );
	shader.loadLights( lights );
	shader.loadViewMatrix( camera );
	renderer.render( entities );
	shader.stop();
	terrain_shader.start();
	terrain_shader.loadClipPlane( clip_plane );
	terrain_shader.loadSkyColour( RED, GREEN, BLUE );
	terrain_shader.loadLights( lights );
	terrain_shader.loadViewMatrix( camera );
	terrain_renderer.render( terrains );
	terrain_shader.stop();
	skybox_renderer.render( camera, glm::vec3( RED, GREEN, BLUE ) );
	terrains.clear();
	entities.clear();
}

void MasterRenderer::renderScene( const std::vector<std::shared_ptr<Entity>>& entities, const std::vector<Terrain>& terrains, const std::vector<std::shared_ptr<Light>>& lights, const Camera& camera
								  , const glm::vec4& clip_plane )
{
	frustum.setCamDef( camera.getPosition(), camera.getLookAt(), glm::vec3( 0, 1, 0 ) );
	for( auto& entity : entities )
	{
		if( frustum.pointInFrustum( entity->getPosition() ) == Frustum::INSIDE )
		{
			processEntity( *entity );
		}
	}

	for( auto& terrain : terrains )
	{
		processTerrain( terrain );
	}

	render( lights, camera, clip_plane );
}

const glm::mat4& MasterRenderer::getProjectionMatrix() const
{
	return projection_matrix;
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
