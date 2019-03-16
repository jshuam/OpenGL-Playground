#include "Terrain.h"

Terrain::Terrain( GLuint x, GLuint z, Loader loader, TerrainTexturePack texture_pack, TerrainTexture blend_map )
	:
	x( x * SIZE ),
	z( z * SIZE ),
	model( generateTerrain( loader ) ),
	texture_pack( texture_pack ),
	blend_map( blend_map )
{}

const GLfloat& Terrain::getX() const
{
	return x;
}

const GLfloat& Terrain::getZ() const
{
	return z;
}

const RawModel& Terrain::getModel() const
{
	return model;
}

const TerrainTexture& Terrain::getBlendMap() const
{
	return blend_map;
}

const TerrainTexturePack& Terrain::getTexturePack() const
{
	return texture_pack;
}

RawModel Terrain::generateTerrain( Loader loader )
{
	GLint count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<GLfloat> vertices( count * 3 );
	std::vector<GLfloat> normals( count * 3 );
	std::vector<GLfloat> texture_coords( count * 2 );
	std::vector<GLint> indices( 6 * ( VERTEX_COUNT - 1 ) * ( VERTEX_COUNT - 1 ) );
	GLint vertexPointer = 0;
	for( GLint i = 0; i < VERTEX_COUNT; i++ )
	{
		for( GLint j = 0; j < VERTEX_COUNT; j++ )
		{
			vertices[vertexPointer * 3] = (GLfloat) j / ( (GLfloat) VERTEX_COUNT - 1 ) * SIZE;
			vertices[vertexPointer * 3 + 1] = 0;
			vertices[vertexPointer * 3 + 2] = (GLfloat) i / ( (GLfloat) VERTEX_COUNT - 1 ) * SIZE;
			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
			texture_coords[vertexPointer * 2] = (GLfloat) j / ( (GLfloat) VERTEX_COUNT - 1 );
			texture_coords[vertexPointer * 2 + 1] = (GLfloat) i / ( (GLfloat) VERTEX_COUNT - 1 );
			vertexPointer++;
		}
	}
	GLint pointer = 0;
	for( GLint gz = 0; gz < VERTEX_COUNT - 1; gz++ )
	{
		for( GLint gx = 0; gx < VERTEX_COUNT - 1; gx++ )
		{
			GLint topLeft = ( gz*VERTEX_COUNT ) + gx;
			GLint topRight = topLeft + 1;
			GLint bottomLeft = ( ( gz + 1 )*VERTEX_COUNT ) + gx;
			GLint bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	return loader.loadToVAO( vertices.data(), indices.data(), texture_coords.data(), normals.data(),
							 vertices.size(), indices.size(), texture_coords.size(), normals.size() );
}
