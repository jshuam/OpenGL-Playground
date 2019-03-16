#pragma once

#include "EntityRenderer.h"
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
	MasterRenderer();
	void createProjectionMatrix();
	void cleanUp();
	void prepare() const;
	void processEntity( const Entity& entity );
	void processTerrain( const Terrain& terrain );
	void render( const Light& light, const Camera& camera );

public:
	static void disableCulling();
	static void enableCulling();

private:
	StaticShader shader;
	EntityRenderer renderer;
	std::unordered_map<TexturedModel, std::vector<Entity>> entities;

	TerrainShader terrain_shader;
	TerrainRenderer terrain_renderer;
	std::vector<Terrain> terrains;

	// Projection Matrix
	static constexpr float FOV = 70.0f;
	static constexpr float NEAR_PLANE = 0.1f;
	static constexpr float FAR_PLANE = 1000.0f;
	glm::mat4 projection_matrix;
};

