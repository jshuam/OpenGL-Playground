#include "TerrainTexturePack.h"

TerrainTexturePack::TerrainTexturePack( const TerrainTexture& background_texture, const TerrainTexture& r_texture,
										const TerrainTexture& g_texture, const TerrainTexture& b_texture )
	:
	background_texture( background_texture ),
	r_texture( r_texture ),
	g_texture( g_texture ),
	b_texture( b_texture )
{}

const TerrainTexture& TerrainTexturePack::getBackgroundTexture() const
{
	return background_texture;
}

const TerrainTexture& TerrainTexturePack::getRTexture() const
{
	return r_texture;
}

const TerrainTexture& TerrainTexturePack::getGTexture() const
{
	return g_texture;
}

const TerrainTexture& TerrainTexturePack::getBTexture() const
{
	return b_texture;
}
