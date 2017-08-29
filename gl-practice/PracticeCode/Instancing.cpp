#include "Instancing.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"
#include "../Utils/Model.h"

// 阵列 不使用Instancing
int arrayWithoutInstancing(GLFWwindow* window)
{

	Shader* shader = new Shader("Instancing/shader1.vsh","Instancing/shader1.fsh");

	GLfloat quadVertices[] = {
		// Positions   // Colors
		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		0.05f, -0.05f,  0.0f, 1.0f, 0.0f,   
		0.05f,  0.05f,  0.0f, 1.0f, 1.0f		    		
	};


	// bind VAO VBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0); 



	// 渲染循环
	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{

		printFPS();

		// 输入
		processInput(window);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		shader->use();
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized


		for (int y = -10; y < 10; y += 2)
		{
			for (int x = -10; x < 10; x += 2)
			{
				glm::vec2 offset;
				offset.x = (float)x / 10.0f + 0.1f;
				offset.y = (float)y / 10.0f + 0.1f;
				shader->setVec2("offset",offset);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}


		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete shader;

	return 0; 
}

// 阵列 使用Instancing
int arrayWithInstancing(GLFWwindow* window)
{

	Shader* shader = new Shader("Instancing/shader2.vsh","Instancing/shader2.fsh");

	GLfloat quadVertices[] = {
		// Positions   // Colors
		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		0.05f, -0.05f,  0.0f, 1.0f, 0.0f,   
		0.05f,  0.05f,  0.0f, 1.0f, 1.0f		    		
	};


	// bind VAO VBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);



	//====================================


	glm::vec2 offset[100];
	int index = 0;
	for (int y = -10; y < 10; y += 2)
	{
		for (int x = -10; x < 10; x += 2)
		{
			glm::vec2 translation;
			translation.x = (float)x / 10.0f + 0.1f;
			translation.y = (float)y / 10.0f + 0.1f;
			offset[index++] = translation;
		}
	}


	// also set instance data
	unsigned int VBOinstance;

	glGenBuffers(1, &VBOinstance);
	glBindBuffer(GL_ARRAY_BUFFER, VBOinstance);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &offset[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, VBOinstance); // this attribute comes from a different vertex buffer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.

	//====================================


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0); 



	// 渲染循环
	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{

		printFPS();


		// 输入
		processInput(window);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		shader->use();
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); // 100 triangles of 6 vertices each

		glBindVertexArray(0);



		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBOinstance);

	delete shader;

	return 0; 
}

// 阵列 使用Instancing 尺寸渐变
int arrayWithInstancingScaling(GLFWwindow* window)
{

	Shader* shader = new Shader("Instancing/shader3.vsh","Instancing/shader3.fsh");

	GLfloat quadVertices[] = {
		// Positions   // Colors
		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		0.05f, -0.05f,  0.0f, 1.0f, 0.0f,   
		0.05f,  0.05f,  0.0f, 1.0f, 1.0f		    		
	};


	// bind VAO VBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);



	//====================================


	glm::vec2 offset[100];
	int index = 0;
	for (int y = -10; y < 10; y += 2)
	{
		for (int x = -10; x < 10; x += 2)
		{
			glm::vec2 translation;
			translation.x = (float)x / 10.0f + 0.1f;
			translation.y = (float)y / 10.0f + 0.1f;
			offset[index++] = translation;
		}
	}


	// also set instance data
	unsigned int VBOinstance;

	glGenBuffers(1, &VBOinstance);
	glBindBuffer(GL_ARRAY_BUFFER, VBOinstance);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &offset[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, VBOinstance); // this attribute comes from a different vertex buffer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.

	//====================================


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0); 



	// 渲染循环
	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{

		printFPS();


		// 输入
		processInput(window);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		shader->use();
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); // 100 triangles of 6 vertices each

		glBindVertexArray(0);



		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBOinstance);

	delete shader;

	return 0; 
}

// 行星带 不使用Instancing
int asteroidFieldWithoutInstancing(GLFWwindow* window)
{

	glEnable(GL_DEPTH_TEST);


	int win_width,win_height;
	glfwGetWindowSize(window,&win_width,&win_height);


	Shader* shader = new Shader("Instancing/shader4.vsh","Instancing/shader4.fsh");

	// Load models
	Model* rock = new Model("rock/rock.obj");
	Model* planet = new Model("planet/planet.obj");

	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 55.0f),glm::vec3(0.0f, 1.0f, 0.0f),-90.0,0.0f);
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	bindCameraToWindow(window, camera);


	// Generate a large list of semi-random model transformation matrices
	GLuint amount = 1000;
	glm::mat4* modelMatrices;
	modelMatrices = new glm::mat4[amount];
	srand(glfwGetTime()); // initialize random seed	
	GLfloat radius = 50.0;
	GLfloat offset = 2.5f;
	for(GLuint i = 0; i < amount; i++)
	{
		glm::mat4 model;
		// 1. Translation: displace along circle with 'radius' in range [-offset, offset]
		GLfloat angle = (GLfloat)i / (GLfloat)amount * 360.0f;
		GLfloat displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat x = sin(angle) * radius + displacement;
		displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat y = displacement * 0.4f; // Keep height of asteroid field smaller compared to width of x and z
		displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// 2. Scale: Scale between 0.05 and 0.25f
		GLfloat scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));		

		// 3. Rotation: add random rotation around a (semi)randomly picked rotation axis vector
		GLfloat rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		// 4. Now add to list of matrices
		modelMatrices[i] = model;
	}






	// 渲染循环
	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{

		printFPS();


		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// 输入
		processInput(window);
		processInput(window, camera, deltaTime);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw triangle
		// Add transformation matrices
		shader->use();

		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera->Zoom, (float)win_width / (float)win_height, 0.1f, 10000.0f);
		shader->setMat4("view", view);
		shader->setMat4("projection", projection);


		// Draw Planet
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		shader->setMat4("model", model);
		planet->Draw(*shader);

		// Draw meteorites
		for(GLuint i = 0; i < amount; i++)
		{
			shader->setMat4("model", glm::value_ptr(modelMatrices[i]));
			rock->Draw(*shader);
		}



		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	delete shader;

	delete planet;
	delete rock;

	unbindCamera(window);
	delete camera;

	delete[] modelMatrices;
	modelMatrices= nullptr;

	return 0; 
}

// 行星带 使用Instancing
int asteroidFieldWithInstancing(GLFWwindow* window)
{

	glEnable(GL_DEPTH_TEST);


	int win_width,win_height;
	glfwGetWindowSize(window,&win_width,&win_height);


	Shader* shaderRock = new Shader("Instancing/shader5.vsh","Instancing/shader5.fsh");
	Shader* shaderPlanet = new Shader("Instancing/shader4.vsh","Instancing/shader4.fsh");

	// Load models
	Model* rock = new Model("rock/rock.obj");
	Model* planet = new Model("planet/planet.obj");

	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 55.0f),glm::vec3(0.0f, 1.0f, 0.0f),-90.0,0.0f);
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	bindCameraToWindow(window, camera);


	// Generate a large list of semi-random model transformation matrices
	GLuint amount = 1000;
	glm::mat4* modelMatrices;
	modelMatrices = new glm::mat4[amount];
	srand(glfwGetTime()); // initialize random seed	
	GLfloat radius = 50.0;
	GLfloat offset = 2.5f;
	for(GLuint i = 0; i < amount; i++)
	{
		glm::mat4 model;
		// 1. Translation: displace along circle with 'radius' in range [-offset, offset]
		GLfloat angle = (GLfloat)i / (GLfloat)amount * 360.0f;
		GLfloat displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat x = sin(angle) * radius + displacement;
		displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat y = displacement * 0.4f; // Keep height of asteroid field smaller compared to width of x and z
		displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// 2. Scale: Scale between 0.05 and 0.25f
		GLfloat scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));		

		// 3. Rotation: add random rotation around a (semi)randomly picked rotation axis vector
		GLfloat rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		// 4. Now add to list of matrices
		modelMatrices[i] = model;
	}


	rock->setupInstanceattribute(5,1000,sizeof(glm::mat4), &modelMatrices[0], 1);



	// 渲染循环
	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{

		printFPS();

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// 输入
		processInput(window);
		processInput(window, camera, deltaTime);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw triangle
		// Add transformation matrices
		shaderPlanet->use();

		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera->Zoom, (float)win_width / (float)win_height, 0.1f, 10000.0f);
		shaderPlanet->setMat4("view", view);
		shaderPlanet->setMat4("projection", projection);



		// Draw Planet
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		shaderPlanet->setMat4("model", model);
		planet->Draw(*shaderPlanet);



		shaderRock->use();
		shaderRock->setMat4("view", view);
		shaderRock->setMat4("projection", projection);

		// Draw meteorites
		rock->drawAsinstanced(shaderRock, amount);


		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	delete shaderRock;
	delete shaderPlanet;

	delete planet;
	delete rock;
	unbindCamera(window);
	delete camera;

	delete[] modelMatrices;
	modelMatrices= nullptr;

	return 0; 
}


