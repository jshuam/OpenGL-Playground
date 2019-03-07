#include "DisplayManager.h"
#include "Loader.h"
#include "Renderer.h"
#include "StaticShader.h"

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
	Renderer renderer;
	StaticShader shader;

	std::vector<GLfloat> vertices =
	{
		-0.5f, 0.5f, 0,  // Vertex 0
		-0.5f, -0.5f, 0, // Vertex 1
		0.5f, -0.5f, 0,  // Vertex 2
		0.5f, 0.5f, 0    // Vertex 3
	};

	std::vector<GLuint> indices = 
	{
		0, 1, 3, // First Triangle
		3, 1, 2  // Second Triangle
	};

	RawModel model = loader.loadToVAO( vertices, indices );

	while( !glfwWindowShouldClose( window ) )
	{
		renderer.prepare();
		shader.start();
		renderer.render( model );
		shader.stop();
		DisplayManager::updateDisplay();
	}

	shader.cleanUp();
	loader.cleanUp();
	DisplayManager::closeDisplay();

	glfwTerminate();
}