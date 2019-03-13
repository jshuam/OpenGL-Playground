#pragma once

#include "Renderer.h"
#include <unordered_map>
#include <vector>

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
	void cleanUp();
	void render( const Light& light, const Camera& camera );
	void processEntity( const Entity& entity );

private:
	StaticShader shader;
	Renderer renderer;
	std::unordered_map<TexturedModel, std::vector<Entity>> entities;
};

