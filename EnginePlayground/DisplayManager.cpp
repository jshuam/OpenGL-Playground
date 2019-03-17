#include "DisplayManager.h"

GLFWwindow* DisplayManager::window;
GLint DisplayManager::pixel_width;
GLint DisplayManager::pixel_height;
GLdouble DisplayManager::delta_time;
std::string DisplayManager::title = "OpenGL Playground - FPS: ";
GLdouble DisplayManager::mouse_d_wheel = 0;