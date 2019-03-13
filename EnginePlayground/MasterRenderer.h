#pragma once

#include "EntityRenderer.h"

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
	void prepare() const;
	glm::mat4& createProjectionMatrix();
	void cleanUp();
	void render( const Light& light, const Camera& camera );
	void processEntity( const Entity& entity );

private:
	StaticShader shader;
	EntityRenderer renderer;
	std::unordered_map<TexturedModel, std::vector<Entity>> entities;

	// Projection Matrix
	static constexpr float FOV = 70.0f;
	static constexpr float NEAR_PLANE = 0.1f;
	static constexpr float FAR_PLANE = 1000.0f;
	glm::mat4 projection_matrix;
};

