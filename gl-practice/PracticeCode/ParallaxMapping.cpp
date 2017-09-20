#include "ParallaxMapping.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"

void _PM_genVBOVAO(GLuint* VBO, GLuint* VAO);


// 视差贴图
int parallaxMapping(GLFWwindow* window)
{

	glEnable(GL_DEPTH_TEST);

	int win_width,win_height;
	glfwGetWindowSize(window,&win_width,&win_height);

	Shader* shader = new Shader("ParallaxMapping/shader1.vsh","ParallaxMapping/shader1.fsh");

	GLuint VAO, VBO;
	_PM_genVBOVAO(&VBO, &VAO);


	unsigned int diffuseMap = TextureLoader::loadTexture("parallax/bricks/diffuse.jpg");
	unsigned int normalMap = TextureLoader::loadTexture("parallax/bricks/normal.jpg");
	unsigned int parallaxMap = TextureLoader::loadTexture("parallax/bricks/normal.jpg");
/*
	unsigned int diffuseMap = TextureLoader::loadTexture("parallax/toy_box/diffuse.png");
	unsigned int normalMap = TextureLoader::loadTexture("parallax/toy_box/normal.png");
	unsigned int parallaxMap = TextureLoader::loadTexture("parallax/toy_box/normal.png");
*/

	// Light source
	glm::vec3 lightPos(0.5f, 1.0f, 0.3f);

	// Camera
	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	bindCameraToWindow(window, camera);


	// =================================================


	shader->use();
	shader->setInt("diffuseMap", 0);
	shader->setInt("normalMap", 1);
	shader->setInt("depthMap", 2);


	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		// 输入
		processInput(window);
		processInput(window, camera, deltaTime);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		glm::mat4 projection = glm::perspective(camera->Zoom, (float)win_width / (float)win_height, 0.1f, 100.0f);
		glm::mat4 view = camera->GetViewMatrix();
		shader->use();
		shader->setMat4("projection", projection);
		shader->setMat4("view", view);
		// render normal-mapped quad
		glm::mat4 model;
		model = glm::rotate(model, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // rotate the quad to show normal mapping from multiple directions
		shader->setMat4("model", model);
		shader->setVec3("viewPos", camera->Position);
		shader->setVec3("lightPos", lightPos);
		shader->setFloat("height_scale", 0.1f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalMap);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, parallaxMap);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		// render light source (simply re-renders a smaller plane at the light's position for debugging/visualization)
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.1f));
		shader->setMat4("model", model);
		//glDrawArrays(GL_TRIANGLES, 0, 6);


		glBindVertexArray(0);



		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}




	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	unbindCamera(window);

	delete shader;
	delete camera;


	return 0;
}

// 视差贴图 陡峭视差映射
int parallaxMappingSteep(GLFWwindow* window)
{

	glEnable(GL_DEPTH_TEST);

	int win_width,win_height;
	glfwGetWindowSize(window,&win_width,&win_height);

	Shader* shader = new Shader("ParallaxMapping/shader2.vsh","ParallaxMapping/shader2.fsh");

	GLuint VAO, VBO;
	_PM_genVBOVAO(&VBO, &VAO);


	unsigned int diffuseMap = TextureLoader::loadTexture("parallax/bricks/diffuse.jpg");
	unsigned int normalMap = TextureLoader::loadTexture("parallax/bricks/normal.jpg");
	unsigned int parallaxMap = TextureLoader::loadTexture("parallax/bricks/normal.jpg");
/*
	unsigned int diffuseMap = TextureLoader::loadTexture("parallax/toy_box/diffuse.png");
	unsigned int normalMap = TextureLoader::loadTexture("parallax/toy_box/normal.png");
	unsigned int parallaxMap = TextureLoader::loadTexture("parallax/toy_box/normal.png");
*/

	// Light source
	glm::vec3 lightPos(0.5f, 1.0f, 0.3f);

	// Camera
	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	bindCameraToWindow(window, camera);


	// =================================================


	shader->use();
	shader->setInt("diffuseMap", 0);
	shader->setInt("normalMap", 1);
	shader->setInt("depthMap", 2);


	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		// 输入
		processInput(window);
		processInput(window, camera, deltaTime);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		glm::mat4 projection = glm::perspective(camera->Zoom, (float)win_width / (float)win_height, 0.1f, 100.0f);
		glm::mat4 view = camera->GetViewMatrix();
		shader->use();
		shader->setMat4("projection", projection);
		shader->setMat4("view", view);
		// render normal-mapped quad
		glm::mat4 model;
		model = glm::rotate(model, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // rotate the quad to show normal mapping from multiple directions
		shader->setMat4("model", model);
		shader->setVec3("viewPos", camera->Position);
		shader->setVec3("lightPos", lightPos);
		shader->setFloat("height_scale", 0.1f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalMap);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, parallaxMap);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		// render light source (simply re-renders a smaller plane at the light's position for debugging/visualization)
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.1f));
		shader->setMat4("model", model);
		//glDrawArrays(GL_TRIANGLES, 0, 6);


		glBindVertexArray(0);



		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}




	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	unbindCamera(window);

	delete shader;
	delete camera;


	return 0;
}

// 视差贴图 视差遮蔽映射
int parallaxMappingOcclusion(GLFWwindow* window)
{

	return 0;
}









void _PM_genVBOVAO(GLuint* VBO, GLuint* VAO)
{

	// calculation for tangent and bitangent of 2 triangles according to 4 pos
	// positions
	glm::vec3 pos1(-1.0f,  1.0f, 0.0f);
	glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
	glm::vec3 pos3( 1.0f, -1.0f, 0.0f);
	glm::vec3 pos4( 1.0f,  1.0f, 0.0f);
	// texture coordinates
	glm::vec2 uv1(0.0f, 1.0f);
	glm::vec2 uv2(0.0f, 0.0f);
	glm::vec2 uv3(1.0f, 0.0f);  
	glm::vec2 uv4(1.0f, 1.0f);
	// normal vector
	glm::vec3 nm(0.0f, 0.0f, 1.0f);

	// calculate tangent/bitangent vectors of both triangles
	glm::vec3 tangent1, bitangent1;
	glm::vec3 tangent2, bitangent2;

	// triangle 1
	// ----------
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent1 = glm::normalize(tangent1);

	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent1 = glm::normalize(bitangent1);

	// triangle 2
	// ----------
	edge1 = pos3 - pos1;
	edge2 = pos4 - pos1;
	deltaUV1 = uv3 - uv1;
	deltaUV2 = uv4 - uv1;

	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent2 = glm::normalize(tangent2);


	bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent2 = glm::normalize(bitangent2);


	float quadVertices[] = {
		// positions            // normal         // texcoords  // tangent                          // bitangent
		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
		pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
	};


	// configure plane VAO
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));


}