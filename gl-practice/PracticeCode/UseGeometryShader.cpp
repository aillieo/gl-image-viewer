#include "UseGeometryShader.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"
#include "../Utils/Model.h"

// 在几何着色器中把点变成线
int gshPointToLine(GLFWwindow* window)
{

	Shader* shader = new Shader("UseGeometryShader/shader1.vsh","UseGeometryShader/shader1.gsh","UseGeometryShader/shader1.fsh");


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
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 



	// 渲染循环
	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{
		// 输入
		processInput(window);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		shader->use();
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_POINTS, 0, 3);


		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete shader;


	return 0; 


}

// 在几何着色器中把点变成“房子”
int gshPointToHouse(GLFWwindow* window)
{

	Shader* shader = new Shader("UseGeometryShader/shader2.vsh","UseGeometryShader/shader2.gsh","UseGeometryShader/shader2.fsh");


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
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 



	// 渲染循环
	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{
		// 输入
		processInput(window);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		shader->use();
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_POINTS, 0, 3);


		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete shader;


	return 0; 


}

// 在几何着色器中把点变成不同颜色的“房子”
int gshPointToHouseColor(GLFWwindow* window)
{
	Shader* shader = new Shader("UseGeometryShader/shader3.vsh","UseGeometryShader/shader3.gsh","UseGeometryShader/shader3.fsh");


	// triangle vertex array
	float vertices[] = {
		// x , y , z , r , g , b
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f , 0.0f, // left  
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f , 0.0f, // right 
		0.0f,  0.5f, 0.0f, 0.0f, 0.0f , 1.0f // top   
	}; 




	// bind VAO VBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 



	// 渲染循环
	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{
		// 输入
		processInput(window);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		shader->use();
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_POINTS, 0, 3);


		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete shader;


	return 0; 
}

// 在几何着色器中把点变成带白色顶部的不同颜色的“房子”
int gshPointToHouseColorWithWhite(GLFWwindow* window)
{
	Shader* shader = new Shader("UseGeometryShader/shader4.vsh","UseGeometryShader/shader4.gsh","UseGeometryShader/shader4.fsh");


	// triangle vertex array
	float vertices[] = {
		// x , y , z , r , g , b
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f , 0.0f, // left  
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f , 0.0f, // right 
		0.0f,  0.5f, 0.0f, 0.0f, 0.0f , 1.0f // top   
	}; 




	// bind VAO VBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 



	// 渲染循环
	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{
		// 输入
		processInput(window);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		shader->use();
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_POINTS, 0, 3);


		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete shader;


	return 0; 
}

// 使用着色器制造爆炸效果
int gshExplode(GLFWwindow* window)
{

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);


	int win_width,win_height;
	glfwGetWindowSize(window,&win_width,&win_height);


	// build and compile shaders
	// -------------------------
	Shader* shader = new Shader("UseGeometryShader/shader5.vsh", "UseGeometryShader/shader5.gsh", "UseGeometryShader/shader5.fsh");

	// load models
	// -----------
	Model* modelObj = new Model("nanosuit/nanosuit.obj");

	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f),glm::vec3(0.0f, 1.0f, 0.0f),-90.0,0.0f);
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	bindCameraToWindow(window, camera);

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);
		processInput(window, camera, deltaTime);

		// render
		// ------
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		shader->use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(camera->Zoom, (float)win_width / (float)win_height, 0.1f, 100.0f);
		glm::mat4 view = camera->GetViewMatrix();
		shader->setMat4("projection", projection);
		shader->setMat4("view", view);

		// render the loaded model
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		shader->setMat4("model", model);


		shader->setFloat("time", glfwGetTime());

		modelObj->Draw(*shader);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	unbindCamera(window);

	delete shader;
	delete modelObj;
	delete camera;

	return 0;
}

// 使用着色器显示法线
int gshDisplayNormals(GLFWwindow* window)
{

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);


	int win_width,win_height;
	glfwGetWindowSize(window,&win_width,&win_height);


	// build and compile shaders
	// -------------------------
	Shader* shader = new Shader("UseGeometryShader/shader7.vsh", "UseGeometryShader/shader7.fsh");
	Shader* shaderNormal = new Shader("UseGeometryShader/shader6.vsh", "UseGeometryShader/shader6.gsh","UseGeometryShader/shader6.fsh");

	// load models
	// -----------
	Model* modelObj = new Model("nanosuit/nanosuit.obj");

	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f),glm::vec3(0.0f, 1.0f, 0.0f),-90.0,0.0f);
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	bindCameraToWindow(window, camera);

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



	// configure a uniform buffer object
	// ---------------------------------
	// first. We get the relevant block indices
	unsigned int uniformBlockIndex1 = glGetUniformBlockIndex(shader->ID, "Mats");
	unsigned int uniformBlockIndex2 = glGetUniformBlockIndex(shaderNormal->ID, "Mats");
	// then we link each shader's uniform block to this uniform binding point
	glUniformBlockBinding(shader->ID, uniformBlockIndex1, 0);
	glUniformBlockBinding(shaderNormal->ID, uniformBlockIndex2, 0);
	// Now actually create the buffer
	unsigned int UBO;
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	// define the range of the buffer that links to a uniform binding point
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, 3 * sizeof(glm::mat4));




	// render loop
	// -----------
	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);
		processInput(window, camera, deltaTime);

		// render
		// ------
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// view/projection transformations
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera->Zoom, (float)win_width / (float)win_height, 0.1f, 100.0f);

		// set the view and projection matrix in the uniform block - we only have to do this once per loop iteration.
		glBindBuffer(GL_UNIFORM_BUFFER, UBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(model));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
		glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		// render the loaded model


		shader->use();
		modelObj->Draw(*shader);
		shaderNormal->use();
		modelObj->Draw(*shaderNormal);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	unbindCamera(window);

	glDeleteBuffers(1, &UBO);

	delete shader;
	delete shaderNormal;
	delete modelObj;
	delete camera;

	return 0;
}
