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

	std::vector<float> vertices = {
		// Left bottom triangle
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		// Right top triangle
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	RawModel model = loader.loadToVAO( vertices );

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