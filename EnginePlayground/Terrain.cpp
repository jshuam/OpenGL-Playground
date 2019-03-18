#include "Maths.h"
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

const GLfloat& Terrain::getTerrainHeight( const GLfloat& world_x, const GLfloat& world_z ) const
{
	GLfloat terrain_x = world_x - this->x;
	GLfloat terrain_z = world_z - this->z;
	GLfloat grid_square_size = SIZE / ( heights.size() - 1 );
	GLint grid_x = glm::floor( terrain_x / grid_square_size );
	GLint grid_z = glm::floor( terrain_z / grid_square_size );
	if( grid_x >= heights.size() - 1 || grid_z >= heights.size() - 1 || grid_x < 0 || grid_z < 0 )
	{
		return 0;
	}
	GLfloat x_coord = glm::modf( terrain_x, grid_square_size ) / grid_square_size;
	GLfloat z_coord = glm::modf( terrain_z, grid_square_size ) / grid_square_size;
	GLfloat answer;
	if( x_coord <= ( 1 - z_coord ) )
	{
		answer = Maths::barryCentric( glm::vec3( 0, heights[grid_z * VERTEX_COUNT + grid_x], 0 ),
									  glm::vec3( 1, heights[grid_z * VERTEX_COUNT + ( grid_x + 1 )], 0 ),
									  glm::vec3( 0, heights[( grid_z + 1 ) * VERTEX_COUNT + grid_x], 1 ), glm::vec2( grid_x, grid_z ) );
	}
	else
	{
		answer = Maths::barryCentric( glm::vec3( 1, heights[grid_z * VERTEX_COUNT + ( grid_x + 1 )], 0 ),
									  glm::vec3( 0, heights[( grid_z + 1 ) * VERTEX_COUNT + grid_x], 1 ),
									  glm::vec3( 1, heights[( grid_z + 1 ) * VERTEX_COUNT + ( grid_x + 1 )], 1 ), glm::vec2( grid_x, grid_z ) );
	}
	return answer;
}

RawModel Terrain::generateTerrain( Loader loader, std::string height_map )
{
	GLint image_width, image_height;
	height_map = "res/" + height_map + ".png";
	stbi_uc* data = stbi_load( height_map.c_str(), &image_width, &image_height, NULL, 1 );

	if( data == nullptr )
	{
		std::cerr << "Failed to height map." << std::endl;
		std::cin.get();
		exit( -1 );
	}

	VERTEX_COUNT = image_height;
	heights.resize( VERTEX_COUNT * VERTEX_COUNT );

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
			GLfloat height = getHeight( j, i, data, image_width, image_height );
			heights[i * VERTEX_COUNT + j] = height;
			vertices[vertexPointer * 3 + 1] = height;
			vertices[vertexPointer * 3 + 2] = (GLfloat) i / ( (GLfloat) VERTEX_COUNT - 1 ) * SIZE;
			glm::vec3 normal = calculateNormal( j, i, data, image_width, image_height );
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
