#include "DisplayManager.h"
#include "Loader.h"
#include "EntityRenderer.h"
#include "StaticShader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "OBJLoader.h"
#include "Light.h"
#include "MasterRenderer.h"

#include <random>

void error_callback( int error, const char* description )
{
	throw std::exception( description );
}

int main()
{
	try
	{
		glfwInit();
	}
	catch( std::exception& e )
	{
		std::cout << "\n" << e.what() << std::endl;
	}

	GLFWwindow* window = DisplayManager::createDisplay( 1280, 720, "OpenGL Playground" );

	Loader loader;
	RawModel tree( OBJLoader::loadObjModel( "lowPolyTree", loader ) );
	RawModel grass( OBJLoader::loadObjModel( "grassModel", loader ) );
	RawModel fern( OBJLoader::loadObjModel( "fern", loader ) );

	TexturedModel tree_texture( tree, loader.loadTexture( "lowPolyTree" ) );
	TexturedModel grass_texture( grass, loader.loadTexture( "grassTexture" ) );
	TexturedModel fern_texture( fern, loader.loadTexture( "fern" ) );

	std::vector<Entity> entities;
	std::uniform_real_distribution<GLfloat> x_dist( 15, 200 );
	std::uniform_real_distribution<GLfloat> z_dist( 15, 200 );
	std::random_device rt;
	std::mt19937 mt( rt() );
	for( int i = 0; i < 500; i++ )
	{
		entities.emplace_back( tree_texture, glm::vec3( x_dist( mt ), -0.5, z_dist( mt ) ), 0, 0, 0, 0.4 );
		entities.emplace_back( fern_texture, glm::vec3( x_dist( mt ), -0.2, z_dist( mt ) ), 0, 0, 0, 0.4 );
		entities.emplace_back( grass_texture, glm::vec3( x_dist( mt ), 0, x_dist( mt ) ), 0, 0, 0, 1 );
	}

	Light light( glm::vec3( 20000, 20000, 2000 ), glm::vec3( 1, 1, 1 ) );

	std::vector<Terrain> terrains;

	terrains.emplace_back( Terrain( 0, 0, loader, ModelTexture( loader.loadTexture( "grass" ) ) ) );

	Camera camera;

	MasterRenderer renderer;
	while( !glfwWindowShouldClose( window ) )
	{
		for( auto& entity : entities )
		{
			renderer.processEntity( entity );
		}
		for( auto& terrain : terrains )
		{
			renderer.processTerrain( terrain );
		}
		camera.move( glfwGetTime() );
		renderer.render( light, camera );
		DisplayManager::updateDisplay();
	}

	renderer.cleanUp();
	loader.cleanUp();
	DisplayManager::closeDisplay();

	glfwTerminate();
}