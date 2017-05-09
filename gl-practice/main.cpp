#include <windows.h>
#include <math.h>

 
#include <stdio.h>  
#include <stdlib.h>  

#include <GL/glew.h>
#include <GLFW/glfw3.h>  
GLFWwindow* window;  

int main( void )  
{  
	if(!glfwInit())  
		return -1;  

	glfwWindowHint(GLFW_SAMPLES,4);  
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);  
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);  

	window = glfwCreateWindow(1024,768,"Test OpenGL config",NULL,NULL);  
	if (!window)  
	{  
		glfwTerminate();  
		return -1;  
	}  

	glfwMakeContextCurrent(window);  

	if(glewInit() != GLEW_OK)  
		return -1;  

	Sleep(1000);

	glfwTerminate();  
	return 0;  
}  