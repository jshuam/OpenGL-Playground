#include "DisplayManager.h"
#include "Loader.h"
#include "Renderer.h"
#include "StaticShader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "OBJLoader.h"
#include "Light.h"

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
	RawModel model( OBJLoader::loadObjModel( "dragon", loader ) );
	TexturedModel textured_model( model, loader.loadTexture( "red" ) );
	ModelTexture texture = textured_model.getTexture();
	texture.setShineDamper( 10 );
	texture.setReflectivity( 1 );
	Entity entity( textured_model, glm::vec3( 0, -0.5, -25 ), 0, 0, 0, 1 );
	Light light( glm::vec3( 200, 200, 100 ), glm::vec3( 1, 1, 1 ) );
	Camera camera;

	while( !glfwWindowShouldClose( window ) )
	{
		entity.increaseRotation( 0, 0.008, 0 );
		camera.move();
		renderer.prepare();
		shader.start();
		shader.loadLight( light );
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