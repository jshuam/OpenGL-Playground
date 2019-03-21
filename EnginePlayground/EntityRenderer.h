#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include "RawModel.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"
#include "Maths.h"
#include <unordered_map>

class EntityRenderer
{
public:
	EntityRenderer() = default;
	EntityRenderer( StaticShader* shader, glm::mat4 projection_matrix, GLuint num_lights );
	void render( const std::unordered_map<TexturedModel, std::vector<Entity>> entities );

private:
	StaticShader* shader;
	void prepareTexturedModel( const TexturedModel& model );
	void unbindTexturedModel();
	void prepareInstance( const Entity& entity );
};

