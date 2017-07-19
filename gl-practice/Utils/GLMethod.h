#ifndef GLMETHOD_H
#define GLMETHOD_H
 
#include <GL/glew.h>
#include <GLFW/glfw3.h>  

GLFWwindow* createWindow();

void processInput(GLFWwindow *window);


void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif