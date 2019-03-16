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

	GLFWwindow* window = DisplayManager::createDisplay( 1280, 720 );

	Loader loader;
	RawModel tree( OBJLoader::loadObjModel( "lowPolyTree", loader ) );
	RawModel grass( OBJLoader::loadObjModel( "grassModel", loader ) );
	RawModel fern( OBJLoader::loadObjModel( "fern", loader ) );

	TexturedModel tree_texture( tree, loader.loadTexture( "lowPolyTree" ) );
	TexturedModel grass_texture( grass, loader.loadTexture( "grassTexture" ) );
	grass_texture.getTexture().setTransparency( true );
	grass_texture.getTexture().setFakeLighting( true );
	TexturedModel fern_texture( fern, loader.loadTexture( "fern" ) );
	fern_texture.getTexture().setTransparency( true );

	std::vector<Entity> entities;
	std::uniform_real_distribution<GLfloat> x_dist( 15, 250 );
	std::uniform_real_distribution<GLfloat> z_dist( 15, 250 );
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
	GLfloat old_dt = glfwGetTime(), timer = old_dt;
	GLfloat new_dt = 0;
	GLfloat dt = 0;
	GLuint frames = 0;
	while( !glfwWindowShouldClose( window ) )
	{
		new_dt = glfwGetTime();
		dt = new_dt - old_dt;
		old_dt = new_dt;
		for( auto& entity : entities )
		{
			renderer.processEntity( entity );
		}
		for( auto& terrain : terrains )
		{
			renderer.processTerrain( terrain );
		}
		camera.move( dt );
		renderer.render( light, camera );
		DisplayManager::updateDisplay();
		frames++;
		if( glfwGetTime() - timer > 1.0 )
		{
			timer++;
			DisplayManager::updateTitle( frames );
			frames = 0;
		}
	}

	renderer.cleanUp();
	loader.cleanUp();
	DisplayManager::closeDisplay();

	glfwTerminate();
}