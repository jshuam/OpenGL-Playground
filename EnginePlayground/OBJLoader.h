#pragma once

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

class OBJLoader
{
	/* ALL CREDIT TO iZastic FOR HIS IMPROVED OBJ LOADER CODE
	 * LINK TO HIS REPO (Shortened) https://goo.gl/5qas4V
	 */
public:
	//static RawModel loadObjModel( const std::string& filename, Loader& loader )
	//{
	//	// Open the file as read only
	//	FILE* file;
	//	if( fopen_s( &file, ( "res/" + filename + ".obj" ).c_str(), "r" ) != 0 )
	//	{
	//		printf( "Failed to open: %s\n", filename.c_str() );
	//	}

	//	// Storage variables
	//	std::vector<float> vertices, f_textures, f_normals;
	//	std::vector<glm::vec2> textures;
	//	std::vector<glm::vec3> normals;
	//	std::vector<int> indices;

	//	char *type, *token, *stop = 0;
	//	char line[256];
	//	while( fgets( line, 256, file ) != NULL )
	//	{
	//		token = NULL;
	//		type = strtok_s( line, " ", &token );
	//		// V is vertex points
	//		if( type[0] == 'v' && type[1] == NULL )
	//		{
	//			// Store a new vertex
	//			vertices.push_back( strtof( token, &stop ) );
	//			token = stop + 1; // Move to the next value
	//			vertices.push_back( strtof( token, &stop ) );
	//			token = stop + 1; // Move to the next value
	//			vertices.push_back( strtof( token, &stop ) );
	//		}
	//		// VT is vertex texture coordinates
	//		else if( type[0] == 'v' && type[1] == 't' )
	//		{
	//			double x = strtod( token, &stop );
	//			token = stop + 1; // Move to the next value
	//			double y = strtod( token, &stop );
	//			// Store a new texture
	//			textures.push_back( glm::vec2( x, y ) );
	//		}
	//		else if( type[0] == 'v' && type[1] == 'n' )
	//		{
	//			double x = strtod( token, &stop );
	//			token = stop + 1; // Move to the next value
	//			double y = strtod( token, &stop );
	//			token = stop + 1; // Move to the next value
	//			double z = strtod( token, &stop );
	//			// Store a new normal
	//			normals.push_back( glm::vec3( x, y, z ) );
	//		}
	//		// F is the index list for faces
	//		else if( type[0] == 'f' )
	//		{
	//			if( indices.size() == 0 )
	//			{
	//				// Set the size of the array
	//				f_textures.resize( ( vertices.size() / 3 ) * 2 );
	//				f_normals.resize( vertices.size() );
	//			}
	//			// Process set of vertex data
	//			processVertices( token, indices, textures, f_textures, normals, f_normals );
	//		}
	//	}
	//	fclose( file );

	//	return loader.loadToVAO( vertices.data(), indices.data(), f_textures.data(), f_normals.data(),
	//							 vertices.size(), indices.size(), f_textures.size(), f_normals.size() );
	//}


	//void static processVertices( char* vertexData, std::vector<int>& indices, std::vector<glm::vec2>& textures,
	//								 std::vector<float>& f_textures, std::vector<glm::vec3>& normals, std::vector<float>& f_normals )
	//{
	//	char *stop;
	//	int vertexPointer;
	//	for( unsigned int i = 0; i < 3; i++ )
	//	{
	//		// Get and store index
	//		vertexPointer = strtol( vertexData, &stop, 10 ) - 1;
	//		indices.push_back( vertexPointer );
	//		vertexData = stop + 1; // Move to the next value
	//		// Get and store texture points
	//		glm::vec2 texture = textures[strtol( vertexData, &stop, 10 ) - 1];
	//		f_textures[vertexPointer * 2] = texture.x;
	//		f_textures[vertexPointer * 2 + 1] = 1 - texture.y;
	//		vertexData = stop + 1; // Move to the next value
	//		// Get and store normal points
	//		glm::vec3 normal = normals[strtol( vertexData, &stop, 10 ) - 1];
	//		f_normals[vertexPointer * 3] = normal.x;
	//		f_normals[vertexPointer * 3 + 1] = normal.y;
	//		f_normals[vertexPointer * 3 + 2] = normal.z;
	//		vertexData = stop + 1; // Move to the next value
	//	}

	//}
	static RawModel loadObjModel( const std::string& filename, Loader& loader )
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn;
		std::string err;
		tinyobj::LoadObj( &attrib, &shapes, &materials, &warn, &err, ( "res/" + filename + ".obj" ).c_str() );

		std::vector<GLint> indices( shapes[0].mesh.indices.size() );
		std::vector<GLfloat> textures( ( attrib.vertices.size() / 3 ) * 2 );
		std::vector<GLfloat> normals( attrib.vertices.size() );

		for( int i = 0; i < shapes[0].mesh.indices.size(); i++ )
		{
			GLint vertex = shapes[0].mesh.indices[i].vertex_index;
			GLint texcoord = shapes[0].mesh.indices[i].texcoord_index;
			GLint normal = shapes[0].mesh.indices[i].normal_index;

			indices[i] = vertex;
			textures[vertex * 2] = attrib.texcoords[texcoord * 2];
			textures[vertex * 2 + 1] = attrib.texcoords[texcoord * 2 + 1];
			normals[vertex * 3] = attrib.normals[normal * 3];
			normals[vertex * 3 + 1] = attrib.normals[normal * 3 + 1];
			normals[vertex * 3 + 2] = attrib.normals[normal * 3 + 2];
		}

		return loader.loadToVAO( attrib.vertices, indices, textures, normals );
	}
};

