#ifndef GLMETHOD_H
#define GLMETHOD_H
 
#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"


GLFWwindow* createWindow();

GLFWwindow* createWindow(int width, int height);

void processInput(GLFWwindow *window);

void processInput(GLFWwindow *window, Camera* camera, float deltaTime);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void bindCameraToWindow(GLFWwindow* window, Camera* camera);
void unbindCamera(GLFWwindow* window);

#endif
