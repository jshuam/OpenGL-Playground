#pragma once

#include "EntityRenderer.h"
#include "SkyboxRenderer.h"
#include "TerrainRenderer.h"
#include "TerrainShader.h"

#include <unordered_map>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

namespace std
{
	template <> struct hash<TexturedModel>
	{
		size_t operator()( const TexturedModel& model ) const
		{
			std::hash<GLuint> hasher;
			auto hash_tid = hasher( model.getTexture().getID() );
			auto hash_rmid = hasher( model.getRawModel().getVaoId() );

			hash_tid ^= hash_rmid + 0x9e3779b9 + ( hash_tid << 6 ) + ( hash_tid >> 2 );
			return hash_tid;
		}
	};
}

class MasterRenderer
{
public:
	MasterRenderer( Loader loader, GLuint num_lights );
	void createProjectionMatrix();
	void cleanUp();
	void prepare() const;
	void processEntity( const Entity& entity );
	void processTerrain( const Terrain& terrain );
	void render( const std::vector<Light>& lights, const Camera& camera );

	const glm::mat4& getProjectionMatrix() const;

public:
	static void disableCulling();
	static void enableCulling();

private:
	StaticShader shader;
	EntityRenderer renderer;
	SkyboxRenderer skybox_renderer;
	std::unordered_map<TexturedModel, std::vector<Entity>> entities;

	TerrainShader terrain_shader;
	TerrainRenderer terrain_renderer;
	std::vector<Terrain> terrains;

	// Projection Matrix
	static constexpr GLfloat FOV = 70.0f;
	static constexpr GLfloat NEAR_PLANE = 0.1f;
	static constexpr GLfloat FAR_PLANE = 1000.0f;
	glm::mat4 projection_matrix;

	static constexpr GLfloat RED = 0.5444f;
	static constexpr GLfloat GREEN = 0.62f;
	static constexpr GLfloat BLUE = 0.69f;
};

