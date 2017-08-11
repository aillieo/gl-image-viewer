#include "FaceCulling.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"



// 使用面剔除
int useFaceCulling(GLFWwindow* window)
{

	// 深度检测 开启
	glEnable(GL_DEPTH_TEST);

	// 开启面剔除
	glEnable(GL_CULL_FACE);

	int win_width,win_height;
	glfwGetWindowSize(window,&win_width,&win_height);


	Shader* shader = new Shader("FaceCulling/shader1.vsh","FaceCulling/shader1.fsh");


	float cubeVertices[] = {
		// x  y  z    s  t	
		// Back face
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right 
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right    

		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left 
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left

		// Front face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right

		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left 
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left

		// Left face
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left  
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right

		// Right face
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right 
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right      

		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left

		// Bottom face          
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left  
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left

		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right

		// Top face
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left      
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f // bottom-left  
  
	};

	float planeVertices[] = {
		// x  y  z    s  t	
		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		5.0f, -0.5f, -5.0f,  2.0f, 2.0f								
	};




	// bind VAO VBO
	unsigned int VBO[2], VAO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 





	// load texture
	glActiveTexture(GL_TEXTURE0);
	unsigned int textureCube = TextureLoader::loadTexture("lighting_maps/diffuseMap.png");
	glActiveTexture(GL_TEXTURE1);
	unsigned int texturePlane = TextureLoader::loadTexture("lighting_maps/specularMap.png");



	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f),-90.0,0.0f);
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	bindCameraToWindow(window, camera);


	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		// 输入
		processInput(window);
		processInput(window, camera, deltaTime);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		shader->use();
		glm::mat4 model;
		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera->Zoom, (float)win_width / (float)win_height, 0.1f, 100.0f);
		shader->setMat4("view", view);
		shader->setMat4("projection", projection);


		// two cubes
		
		// enable face culling
		// face front only
		glCullFace(GL_BACK);
		glBindVertexArray(VAO[0]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureCube); 	
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		shader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// face back only
		glCullFace(GL_FRONT);
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		shader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);



		// floor
		glDisable(GL_CULL_FACE);
		glBindVertexArray(VAO[1]);
		glBindTexture(GL_TEXTURE_2D, texturePlane);
		model = glm::mat4();
		// avoid z-fighting
		model = glm::translate(model, glm::vec3(0.0f, - 0.01f, 0.0f));
		shader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glEnable(GL_CULL_FACE);

		glBindVertexArray(0);


		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}




	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);


	unbindCamera(window);

	delete shader;
	delete camera;

	return 0;
}
