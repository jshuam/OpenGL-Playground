#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <exception>
#include <string>
#include <iostream>

class DisplayManager
{
public:
	static GLFWwindow* createDisplay( int width, int height, std::string title = title )
	{
		// Specifying minimum version of OpenGL that will be used
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
		glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

		// Setting callback functions
		glfwSetScrollCallback( window, scrollCallback );

		// Creating window with passed in width, height and title
		try
		{
			window = glfwCreateWindow( width, height, title.c_str(), NULL, NULL );
		}
		catch( std::exception& e )
		{
			std::cout << "\n" << e.what() << std::endl;
		}

		// Setting the OpenGL context to be the newly created window
		glfwMakeContextCurrent( window );
		// Using glad to load modern GL function pointers
		gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );

		// Getting screen size in pixels for the GL viewport
		// This is needed as window coords are often different to real screen pixel coords
		glfwGetFramebufferSize( window, &pixel_width, &pixel_height );
		glViewport( 0, 0, pixel_width, pixel_height );

		glfwSwapInterval( 0 );

		return window;
	}
	static void updateDisplay()
	{
		// Swapping the front and back buffer to update the display
		glfwSwapBuffers( window );
		glfwPollEvents();
	}
	static void updateTitle( const GLuint& fps )
	{
		glfwSetWindowTitle( window, ( title + std::to_string( fps ) ).c_str() );
	}
	static void closeDisplay()
	{
		glfwDestroyWindow( window );
	}
	static const GLint getWidth()
	{
		return pixel_width;
	}
	static const GLint getHeight()
	{
		return pixel_height;
	}
	static const GLdouble& getMouseDWheel()
	{
		return mouse_d_wheel;
	}
	static const GLdouble& getMouseXPos()
	{
		return mouse_x_pos;
	}
	static const GLdouble& getMouseYPos()
	{
		return mouse_y_pos;
	}
	static const GLint getKey( const GLint& key )
	{
		return glfwGetKey( window, key );
	}
	static void scrollCallback( GLFWwindow* window, double x_offset, double y_offset )
	{
		mouse_d_wheel = x_offset;
	}
	static void cursorCallback( GLFWwindow* window, double x_position, double y_position )
	{
		mouse_x_pos = x_position;
		mouse_x_pos = y_position;
	}

private:
	static GLFWwindow* window;
	static GLint pixel_width;
	static GLint pixel_height;
	static GLdouble delta_time;
	static std::string title;
	static GLdouble mouse_d_wheel;
	static GLdouble mouse_x_pos;
	static GLdouble mouse_y_pos;
};