#include "DisplayManager.h"

GLFWwindow* DisplayManager::window;
GLint DisplayManager::pixel_width;
GLint DisplayManager::pixel_height;
GLdouble DisplayManager::delta_time;
std::string DisplayManager::title = "OpenGL Playground - FPS: ";
GLdouble DisplayManager::mouse_d_wheel = 0;
GLdouble DisplayManager::mouse_x_pos = 0;
GLdouble DisplayManager::mouse_y_pos = 0;
GLdouble DisplayManager::mouse_x_offset = 0;
GLdouble DisplayManager::mouse_y_offset = 0;
GLboolean DisplayManager::mouse_scrolling = false;
GLboolean DisplayManager::mouse_l_click = false;
GLboolean DisplayManager::mouse_r_click = false;
GLfloat DisplayManager::old_dt = glfwGetTime();
GLfloat DisplayManager::new_dt = 0;
GLfloat DisplayManager::dt = 0;
