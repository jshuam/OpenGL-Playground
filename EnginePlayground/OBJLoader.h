#pragma once

#include <string>
#include "Loader.h"
#include "RawModel.h"
#include "Utils.h"
#include <fstream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class OBJLoader
{
public:
	static RawModel loadObjModel( std::string filename, Loader loader )
	{
		std::fstream in( filename + ".obj" );

		// These are for storing the initial read in values (which are out of order)
		std::vector<glm::vec2> textures;
		std::vector<glm::vec3> normals;

		/* These are for storing the indices, textures and normals in order.
		 * The reasoning for this is because Blender initially writes everything out of order,
		 * So we need to re-order it so that a indice (that points to a vertex) lines up with its
		 * appropriate texture/normal.
		 * I.e. 41/2/2, Index 41 (-1 as Blender is 1 based) uses textures at position 2 and normals at position 2
		 * Which keep in mind are at Index * 2 for textures (as there are 2 floats per texture)
		 * And index * 3 for normals as there are 3 normal floats per vertex
		 */
		std::vector<GLfloat> vertices;
		std::vector<GLuint> indices;
		std::vector<GLfloat> f_textures;
		std::vector<GLfloat> f_normals;

		std::string line;
		std::getline( in, line );

		while( !in.eof() )
		{
			std::vector<std::string> split = Utils::split( line );

			if( split.size() == 0 )
			{
				continue;
			}
			else if( split[0] == "v" )
			{
				for( GLint i = 1; i <= 3; i++ )
				{
					vertices.push_back( std::stof( split[i] ) );
				}
			}
			else if( split[0] == "vt" )
			{
				glm::vec2 texture { std::stof( split[1] ), std::stof( split[2] ) };
				textures.push_back( texture );
			}
			else if( split[0] == "vn" )
			{
				glm::vec3 normal { std::stof( split[1] ), std::stof( split[2] ), std::stof( split[3] ) };
				normals.push_back( normal );
			}
			else if( split[0] == "s" )
			{
				// Reserving sizes for the vectors
				f_textures.resize( ( vertices.size() / 2 ) * 2 );
				f_normals.resize( vertices.size() );
				break;
			}

			std::getline( in, line );
		}

		std::getline( in, line );

		while( !in.eof() )
		{
			std::vector<std::string> split = Utils::split( line );
			char delimiter = '/';
			// Vertex 1's Data
			std::vector<std::string> vertex_1 = Utils::split( split[1], '/' );
			// Vertex 2's Data
			std::vector<std::string> vertex_2 = Utils::split( split[2], '/' );
			// Vertex 3's Data
			std::vector<std::string> vertex_3 = Utils::split( split[3], '/' );

			processVertex( vertex_1, indices, textures, normals, f_textures, f_normals );
			processVertex( vertex_2, indices, textures, normals, f_textures, f_normals );
			processVertex( vertex_3, indices, textures, normals, f_textures, f_normals );

			std::getline( in, line );
		}

		in.close();

		return loader.loadToVAO( vertices, f_textures, indices );
	}

private:
	static void processVertex( std::vector<std::string>& vertex_data, std::vector<GLuint>& indices,
							   std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals,
							   std::vector<GLfloat>& f_textures, std::vector<GLfloat>& f_normals )
	{
		GLuint current_vertex = std::stoi( vertex_data[0] ) - 1;
		GLuint current_texture = std::stoi( vertex_data[1] ) - 1;
		GLuint current_normal = std::stoi( vertex_data[2] ) - 1;
		indices.push_back( current_vertex );
		f_textures[current_vertex * 2] = textures[current_texture].x;
		// 1 - here as OpenGL starts from top left, Blender starts from bottom left (of textures)
		f_textures[current_vertex * 2 + 1] = ( 1 - textures[current_texture].y );
		f_normals[current_vertex * 3] = normals[current_normal].x;
		f_normals[current_vertex * 3 + 1] = normals[current_normal].y;
		f_normals[current_vertex * 3 + 2] = normals[current_normal].z;
	}
};

