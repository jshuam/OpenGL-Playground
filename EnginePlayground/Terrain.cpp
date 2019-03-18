#include "Terrain.h"

#include <cassert>
#include <iostream>
#include <glm/geometric.hpp>

Terrain::Terrain( GLuint x, GLuint z, Loader loader, TerrainTexturePack texture_pack, TerrainTexture blend_map, std::string height_map )
	:
	x( x * SIZE ),
	z( z * SIZE ),
	model( generateTerrain( loader, height_map ) ),
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

RawModel Terrain::generateTerrain( Loader loader, std::string height_map )
{
	GLint width, height;
	height_map = "res/" + height_map + ".png";
	stbi_uc* data = stbi_load( height_map.c_str(), &width, &height, NULL, 1 );

	if( data == nullptr )
	{
		std::cerr << "Failed to height map." << std::endl;
		std::cin.get();
		exit( -1 );
	}
	GLint VERTEX_COUNT = height;

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
			vertices[vertexPointer * 3 + 1] = getHeight(j, i, data, width, height);
			vertices[vertexPointer * 3 + 2] = (GLfloat) i / ( (GLfloat) VERTEX_COUNT - 1 ) * SIZE;
			glm::vec3 normal = calculateNormal( j, i, data, width, height );
			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;
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
	return loader.loadToVAO( vertices, indices, texture_coords, normals );
}

GLfloat Terrain::getHeight( GLuint x, GLuint y, stbi_uc* image, GLint image_width, GLint image_height )
{
	if( x < 0 || x >= image_height || y < 0 || y >= image_height )
	{
		return 0;
	}

	GLfloat height = image[image_width * y + x];
	height -= MAX_PIXEL_COLOUR;
	height /= MAX_PIXEL_COLOUR;
	height *= MAX_HEIGHT;
	return height;
}

glm::vec3 Terrain::calculateNormal( GLuint x, GLuint z, stbi_uc* image, GLint image_width, GLint image_height )
{
	GLfloat heightL = getHeight( x - 1, z, image, image_width, image_height );
	GLfloat heightR = getHeight( x + 1, z, image, image_width, image_height );
	GLfloat heightD = getHeight( x, z - 1, image, image_width, image_height );
	GLfloat heightU = getHeight( x, z + 1, image, image_width, image_height );
	glm::vec3 normal( heightL - heightR, 2.0f, heightD - heightU );
	return glm::normalize( normal );
}
