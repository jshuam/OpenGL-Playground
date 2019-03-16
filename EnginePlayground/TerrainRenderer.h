#pragma once

#include "Entity.h"
#include "Terrain.h"
#include "TerrainShader.h"
#include "TexturedModel.h"

class TerrainRenderer
{
public:
	TerrainRenderer() = default;
	TerrainRenderer( TerrainShader shader, glm::mat4 projection_matrix );
	~TerrainRenderer() = default;
	void render( const std::vector<Terrain>& terrains ) const;
	void prepareTerrain( const Terrain& terrain ) const;
	void unbindTexturedModel() const;
	void loadModelMatrix( const Terrain& terrain ) const;

private:
	TerrainShader shader;

private:
	void bindTextures( const Terrain& terrain ) const;
};

