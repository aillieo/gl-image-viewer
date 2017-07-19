#include "GLMethod.h"

GLFWwindow* createWindow()
{
	if(!glfwInit())  
		return nullptr;  

	glfwWindowHint(GLFW_SAMPLES,4);  
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);  
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);  


#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	GLFWwindow* window = glfwCreateWindow(1024,768,"Test OpenGL config",NULL,NULL);  
	if (!window)  
	{  
		glfwTerminate();  
		return nullptr;  
	}  

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if(glewInit() != GLEW_OK)  
		return nullptr;  


	return window;
}


void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}