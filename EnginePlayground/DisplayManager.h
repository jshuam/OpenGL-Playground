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

		// Creating window with passed in width, height and title
		try
		{
			window = glfwCreateWindow( width, height, title.c_str(), NULL, NULL );
		}
		catch( std::exception& e )
		{
			std::cout << "\n" << e.what() << std::endl;
		}

		// Setting callback functions
		glfwSetScrollCallback( window, scrollCallback );
		glfwSetCursorPosCallback( window, cursorCallback );
		glfwSetMouseButtonCallback( window, mouseButtonCallback );

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
		return mouse_x_offset;
	}
	static const GLdouble& getMouseYPos()
	{
		return mouse_y_offset;
	}
	static const GLint& getKey( const GLint& key )
	{
		return glfwGetKey( window, key );
	}
	static GLboolean& mouseScrolling()
	{
		return mouse_scrolling;
	}
	static GLboolean& mouseLClick()
	{
		return mouse_l_click;
	}
	static GLboolean& mouseRClick()
	{
		return mouse_r_click;
	}
	static void mouseButtonCallback( GLFWwindow* window, int button, int action, int mods )
	{
		if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS )
		{
			mouse_l_click = true;
		}
		else if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE )
		{
			mouse_l_click = false;
		}
		if( button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS )
		{
			mouse_r_click = true;
		}
		else if( button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE )
		{
			mouse_r_click = false;
		}
	}
	static void scrollCallback( GLFWwindow* window, double x_offset, double y_offset )
	{
		mouse_scrolling = true;
		mouse_d_wheel = y_offset;
	}
	static void cursorCallback( GLFWwindow* window, double x_position, double y_position )
	{
		mouse_x_offset = x_position - mouse_x_pos;
		mouse_y_offset = y_position - mouse_y_pos;
		mouse_x_pos = x_position;
		mouse_y_pos = y_position;
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
	static GLdouble mouse_x_offset;
	static GLdouble mouse_y_offset;
	static GLboolean mouse_scrolling;
	static GLboolean mouse_l_click;
	static GLboolean mouse_r_click;
};