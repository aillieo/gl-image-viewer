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

#include "HelloTriangle.h"

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

const char *fragmentShaderSourceBlue = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
	"}\n\0";


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

int prepareShaders(const char* vsh, const char* fsh)
{

	// shaders
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vsh, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fsh, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	return shaderProgram;

}




int drawHelloTriangleVAO()
{

		if(0 != initWindow())
	{
		return -1;
	}

	int shaderProgram = prepareShaders(vertexShaderSource,fragmentShaderSource);


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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);



	glfwTerminate();  
	return 0; 


}

int drawTwoTriangleNoEBO()
{

		if(0 != initWindow())
	{
		return -1;
	}
	//Sleep(1000);

	float vertices[] = {

		-0.5f, 0.5f, 0.0f,   // 1-左上角 
		-0.5f, -0.5f, 0.0f, // 1-左下角
		0.5f, 0.5f, 0.0f,   // 1-右上角
 		-0.4f, -0.5f, 0.0f, // 2-左下角
		0.5f, 0.4f, 0.0f,   // 2-右上角
 		0.5f, -0.5f, 0.0f  // 2-右下角

	}; 

	int shaderProgram = prepareShaders(vertexShaderSource,fragmentShaderSource);


	// triangle vertex array





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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 6);


		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);



	glfwTerminate();  
	return 0;   

}

int drawTwoTriangleEBO()
{


	if(0 != initWindow())
	{
		return -1;
	}
	//Sleep(1000);



	int shaderProgram = prepareShaders(vertexShaderSource,fragmentShaderSource);

	// triangle vertex array
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};

	unsigned int indices[] = { // 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	}; 




	// bind VAO VBO EBO
	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0); 

		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);



	glfwTerminate();  
	return 0;   
}



int drawTwoTriangleTwoVAO()
{
	
	if(0 != initWindow())
	{
		return -1;
	}
	//Sleep(1000);



	int shaderProgram = prepareShaders(vertexShaderSource,fragmentShaderSource);


	// triangle vertex array
	float vertices_0[] = {

		-0.5f, 0.5f, 0.0f,   // 1-左上角 
		-0.5f, -0.5f, 0.0f, // 1-左下角
		0.5f, 0.5f, 0.0f   // 1-右上角
	}; 

	float vertices_1[] = {
 		-0.4f, -0.5f, 0.0f, // 2-左下角
		0.5f, 0.4f, 0.0f,   // 2-右上角
 		0.5f, -0.5f, 0.0f  // 2-右下角

	}; 



	// bind VAO VBO
	unsigned int VAO[2], VBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_0), vertices_0, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);




	glBindBuffer(GL_ARRAY_BUFFER, 0); 

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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO[0]); 
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(VAO[1]); 
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);



	glfwTerminate();  
	
	return 0;   
}


int drawHelloTriangleTwoShader()
{
		if(0 != initWindow())
	{
		return -1;
	}
	//Sleep(1000);



	int shaderProgram_0 = prepareShaders(vertexShaderSource,fragmentShaderSource);
	int shaderProgram_1 = prepareShaders(vertexShaderSource,fragmentShaderSourceBlue);

	// triangle vertex array
	float vertices_0[] = {

		-0.5f, 0.5f, 0.0f,   // 1-左上角 
		-0.5f, -0.5f, 0.0f, // 1-左下角
		0.5f, 0.5f, 0.0f   // 1-右上角
	}; 

	float vertices_1[] = {
 		-0.4f, -0.5f, 0.0f, // 2-左下角
		0.5f, 0.4f, 0.0f,   // 2-右上角
 		0.5f, -0.5f, 0.0f  // 2-右下角

	}; 



	// bind VAO VBO
	unsigned int VAO[2], VBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_0), vertices_0, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);




	glBindBuffer(GL_ARRAY_BUFFER, 0); 

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
		glUseProgram(shaderProgram_0);
		glBindVertexArray(VAO[0]); 
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgram_1);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);



	glfwTerminate();  
	
	return 0;   
}

int drawHelloTriangleTwoShaderEBO()
{
	
	if(0 != initWindow())
	{
		return -1;
	}

	int shaderProgram_0 = prepareShaders(vertexShaderSource,fragmentShaderSource);
	int shaderProgram_1 = prepareShaders(vertexShaderSource,fragmentShaderSourceBlue);


	// triangle vertex array
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};

	unsigned int indices_0[] = { // 注意索引从0开始! 
		0, 1, 3 // 第一个三角形
	}; 

	unsigned int indices_1[] = { // 注意索引从0开始! 
		1, 2, 3  // 第二个三角形
	}; 



	// bind VAO VBO EBO
	unsigned int VBO, VAO[2], EBO[2];

	glGenVertexArrays(2, VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(2, EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_0), indices_0, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_1), indices_1, GL_STATIC_DRAW);

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
		glUseProgram(shaderProgram_0);
		glBindVertexArray(VAO[0]); 
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glUseProgram(shaderProgram_1);
		glBindVertexArray(VAO[1]); 
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(0); 

		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(2, EBO);



	glfwTerminate();  
	return 0;   
}
