#include "OBJLoader.h"
#include <fstream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

RawModel OBJLoader::loadObjModel( std::string filename, Loader loader )
{
	std::fstream in( filename );

	glm::vec3 vertices;
	glm::vec2 textures;
	glm::vec3 normals;
	std::vector<int> indices;

	std::string line;
	std::getline( in, line );

	while( !in.eof() )
	{


		std::getline( in, line );
	}
}
