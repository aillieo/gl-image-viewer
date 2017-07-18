#include "SimpleShader.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif
#include <math.h>


#include <stdio.h>  
#include <stdlib.h>  

#include <GL/glew.h>
#include <GLFW/glfw3.h>  
#include <iostream>

#include "../Utils/Shader.h"


GLFWwindow* window;  

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int initWindow()
{
	if(!glfwInit())  
		return -1;  

	glfwWindowHint(GLFW_SAMPLES,4);  
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);  
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);  


#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	window = glfwCreateWindow(1024,768,"Test OpenGL config",NULL,NULL);  
	if (!window)  
	{  
		glfwTerminate();  
		return -1;  
	}  

	glfwMakeContextCurrent(window);  

	if(glewInit() != GLEW_OK)  
		return -1;  


	return 0;
}

int useShaderClass()
{

	if(0 != initWindow())
	{
		return -1;
	}

	Shader* shader = new Shader("../../gl-practice/_shaders/shader1.vsh","../../gl-practice/_shaders/shader1.fsh");


	// triangle vertex array
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, // right 
		0.0f,  0.5f, 0.0f  // top   
	}; 




	// bind VAO VBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0); 




	// 渲染循环
	while(!glfwWindowShouldClose(window))
	{
		// 输入
		processInput(window);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		shader->use();
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete shader;

	glfwTerminate();  
	return 0; 


}


int colorFromVSH()
{

	return 0;
}
