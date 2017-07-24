#ifndef GLMETHOD_H
#define GLMETHOD_H
 
#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

GLFWwindow* createWindow();

GLFWwindow* createWindow(int width, int height);

void processInput(GLFWwindow *window);


void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif
