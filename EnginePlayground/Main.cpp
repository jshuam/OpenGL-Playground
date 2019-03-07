#include "DisplayManager.h"
#include "Loader.h"
#include "Renderer.h"

void error_callback( int error, const char* description )
{
	throw std::exception( description );
}

int main()
{
	glfwInit();

	GLFWwindow* window = DisplayManager::createDisplay( 1280, 720, "OpenGL Playground" );

	Loader loader;
	Renderer renderer;

	std::vector<GLfloat> vertices =
	{
		-0.5f, 0.5f, 0,  // Vertice 0
		-0.5f, -0.5f, 0, // Vertice 1
		0.5f, -0.5f, 0,  // Vertice 2
		0.5f, 0.5f, 0    // Vertice 3
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
		renderer.render( model );
		DisplayManager::updateDisplay();
	}

	loader.cleanUp();
	DisplayManager::closeDisplay();

	glfwTerminate();
}