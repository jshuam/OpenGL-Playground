#pragma once

#include "TerrainTexture.h"

class TerrainTexturePack
{
public:
	TerrainTexturePack() = default;
	TerrainTexturePack( const TerrainTexture& background_texture, const TerrainTexture& r_texture,
						const TerrainTexture& g_texture, const TerrainTexture& b_texture );

public:
	const TerrainTexture& getBackgroundTexture() const;
	const TerrainTexture& getRTexture() const;
	const TerrainTexture& getGTexture() const;
	const TerrainTexture& getBTexture() const;

private:
	TerrainTexture background_texture;
	TerrainTexture r_texture;
	TerrainTexture g_texture;
	TerrainTexture b_texture;
};

