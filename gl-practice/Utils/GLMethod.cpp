#include "GLMethod.h"
#include "../SceneManager.h"

int LastPressedKey = 0;

GLFWwindow* createWindow(int width, int height)
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

	GLFWwindow* window = glfwCreateWindow(width,height,"Test OpenGL config",NULL,NULL);  
	if (!window)  
	{  
		glfwTerminate();  
		return nullptr;  
	}  

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if(glewInit() != GLEW_OK)  
		return nullptr;  


	return window;
}


void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return;
	}

	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		LastPressedKey = GLFW_KEY_LEFT;
	}
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		LastPressedKey = GLFW_KEY_RIGHT;
	}


	//

	if(LastPressedKey > 0 && glfwGetKey(window, LastPressedKey) == GLFW_RELEASE)
	{
		if (LastPressedKey == GLFW_KEY_RIGHT)
		{
			SceneManager::toNext();
		}
		else if (LastPressedKey == GLFW_KEY_LEFT)
		{ 
			SceneManager::toPrevious();
		}
		LastPressedKey = 0;
	}

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


GLFWwindow* createWindow()
{
	return createWindow(1024,768);
}


void processInput(GLFWwindow *window, Camera* camera, float deltaTime)
{

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);

}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{


}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{


}

