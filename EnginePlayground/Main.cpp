#include "DisplayManager.h"
#include "Loader.h"
#include "Renderer.h"
#include "StaticShader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "OBJLoader.h"
#include "Light.h"
#include "MasterRenderer.h"

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
	RawModel model( OBJLoader::loadObjModel( "dragon", loader ) );
	TexturedModel textured_model( model, loader.loadTexture( "red" ) );
	textured_model.getTexture().setShineDamper( 1000 );
	textured_model.getTexture().setReflectivity( 100 );
	Entity entity( textured_model, glm::vec3( 0, -0.5, -25 ), 0, 0, 0, 1 );
	Light light( glm::vec3( 200, 200, 100 ), glm::vec3( 1, 1, 1 ) );
	Camera camera;

	MasterRenderer renderer;
	while( !glfwWindowShouldClose( window ) )
	{
		entity.increaseRotation( 0, 0.08, 0 );
		renderer.processEntity( entity );
		camera.move();
		renderer.render( light, camera );
		DisplayManager::updateDisplay();
	}

	renderer.cleanUp();
	loader.cleanUp();
	DisplayManager::closeDisplay();

	glfwTerminate();
}