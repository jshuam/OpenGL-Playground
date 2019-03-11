#include "DisplayManager.h"
#include "Loader.h"
#include "Renderer.h"
#include "StaticShader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "OBJLoader.h"

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
	StaticShader shader;
	Renderer renderer( shader );
	RawModel model( OBJLoader::loadObjModel( "stall", loader ) );
	TexturedModel textured_model( model, loader.loadTexture( "stallTexture" ) );
	Entity entity( textured_model, glm::vec3( 0, -5, -50 ), 0, 0, 0, 1 );
	Camera camera;

	while( !glfwWindowShouldClose( window ) )
	{
		camera.move();
		renderer.prepare();
		shader.start();
		shader.loadViewMatrix( camera );
		renderer.render( entity, shader );
		shader.stop();
		DisplayManager::updateDisplay();
	}

	shader.cleanUp();
	loader.cleanUp();
	DisplayManager::closeDisplay();

	glfwTerminate();
}