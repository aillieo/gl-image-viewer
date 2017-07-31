#include "BasicMaterials.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"

#include "../SceneManager.h"


int useMaterials(GLFWwindow* window)
{
    // 开启深度检测
    glEnable(GL_DEPTH_TEST);
    
    int win_width,win_height;
    glfwGetWindowSize(window,&win_width,&win_height);
    
    
    
    // SHADER
    Shader* shaderLight = new Shader("BasicMaterials/shader1.vsh","BasicMaterials/shader1.fsh");
    Shader* shader = new Shader("BasicMaterials/material1.vsh","BasicMaterials/material1.fsh");
    
    
    // VERTICES:
    // x, y, z, s, t
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    
    
    
    // bind VAO VBO
    unsigned int VBO, VAO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
    
    glm::vec3 lightPos;
    Camera* camera = new Camera(glm::vec3(1.5f, 2.0f, 3.0f),glm::vec3(0.0f, 1.0f, 0.0f),-120.0f,-28.0f);
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    
    
    
    glm::mat4 model;
    
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)win_width / (float)win_height, 0.1f, 100.0f);
    
    // 渲染循环
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
        
        
        glm::mat4 view = camera->GetViewMatrix();
        
        double time = glfwGetTime();
        lightPos = glm::vec3(1.0f * sin(time), 0.8 + 0.2f * sin(time * 7.0f), 1.0f * cos(time));
        //lightPos = glm::vec3(0.1f, 1.0f, 2.0f);
        glm::mat4 modelLight;
        modelLight = glm::translate(modelLight, lightPos);
        modelLight = glm::scale(modelLight, glm::vec3(0.05,0.1,0.05));
        
        
        // LIGHT
        shaderLight->use();
        shaderLight->setMat4("model", glm::value_ptr(modelLight));
        shaderLight->setMat4("view", glm::value_ptr(view));
        shaderLight->setMat4("projection", glm::value_ptr(projection));
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0,36);
        
        
        
        // OBJECT
        shader->use();
        shader->setMat4("model", glm::value_ptr(model));
        shader->setMat4("view", glm::value_ptr(view));
        shader->setMat4("projection", glm::value_ptr(projection));
        
        glm::vec3 lightColor = glm::vec3(1.0,1.0,1.0);
        
        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
        shader->setVec3("light.ambient", ambientColor);
        shader->setVec3("light.diffuse", diffuseColor);
        shader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        
        // material properties
        shader->setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
        shader->setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
        shader->setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f)); // specular lighting doesn't have full effect on this object's material
        shader->setFloat("material.shininess", 32.0f);
        
        shader->setVec3("light.position", glm::value_ptr(lightPos));
        shader->setVec3("viewPos", glm::value_ptr(camera->Position));
        
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0,36);
        
        
        // 检查并调用事件，交换缓冲
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    delete shader;
    delete shaderLight;
    delete camera;
    
    return 0;
}


// 青色塑料盒子
int cyanPlasticBox(GLFWwindow* window)
{
	// 开启深度检测
	glEnable(GL_DEPTH_TEST);

	int win_width,win_height;
	glfwGetWindowSize(window,&win_width,&win_height);



	// SHADER
	Shader* shaderLight = new Shader("BasicMaterials/shader1.vsh","BasicMaterials/shader1.fsh");
	Shader* shader = new Shader("BasicMaterials/material1.vsh","BasicMaterials/material1.fsh");


	// VERTICES:
	// x, y, z, s, t
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};



	// bind VAO VBO
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


	glm::vec3 lightPos;
	Camera* camera = new Camera(glm::vec3(1.5f, 2.0f, 3.0f),glm::vec3(0.0f, 1.0f, 0.0f),-120.0f,-28.0f);
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;



	glm::mat4 model;

	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)win_width / (float)win_height, 0.1f, 100.0f);

	// 渲染循环
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


		glm::mat4 view = camera->GetViewMatrix();

		double time = glfwGetTime();
		lightPos = glm::vec3(1.0f * sin(time), 0.8 + 0.2f * sin(time * 7.0f), 1.0f * cos(time));
		//lightPos = glm::vec3(0.1f, 1.0f, 2.0f);
		glm::mat4 modelLight;
		modelLight = glm::translate(modelLight, lightPos);
		modelLight = glm::scale(modelLight, glm::vec3(0.05,0.1,0.05));


		// LIGHT
		shaderLight->use();
		shaderLight->setMat4("model", glm::value_ptr(modelLight));
		shaderLight->setMat4("view", glm::value_ptr(view));
		shaderLight->setMat4("projection", glm::value_ptr(projection));
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0,36);



		// OBJECT
		shader->use();
		shader->setMat4("model", glm::value_ptr(model));
		shader->setMat4("view", glm::value_ptr(view));
		shader->setMat4("projection", glm::value_ptr(projection));

		glm::vec3 lightColor = glm::vec3(1.0,1.0,1.0);

		// light properties
		shader->setVec3("light.ambient", glm::vec3(1.0f, 1.0f, 1.0f)); // note that all light colors are set at full intensity
		shader->setVec3("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		// material properties
		shader->setVec3("material.ambient", glm::vec3(0.0f, 0.1f, 0.06f));
		shader->setVec3("material.diffuse", glm::vec3(0.0f, 0.50980392f, 0.50980392f));
		shader->setVec3("material.specular", glm::vec3(0.50196078f, 0.50196078f, 0.50196078f));
		shader->setFloat("material.shininess", 32.0f);

		shader->setVec3("light.position", glm::value_ptr(lightPos));
		shader->setVec3("viewPos", glm::value_ptr(camera->Position));

		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0,36);


		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete shader;
	delete shaderLight;
	delete camera;

	return 0;
}


// 通用 指定材质属性
int boxWithMaterial(GLFWwindow* window, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{

	// 开启深度检测
	glEnable(GL_DEPTH_TEST);

	int win_width,win_height;
	glfwGetWindowSize(window,&win_width,&win_height);



	// SHADER
	Shader* shaderLight = new Shader("BasicMaterials/shader1.vsh","BasicMaterials/shader1.fsh");
	Shader* shader = new Shader("BasicMaterials/material1.vsh","BasicMaterials/material1.fsh");


	// VERTICES:
	// x, y, z, s, t
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};



	// bind VAO VBO
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


	glm::vec3 lightPos;
	Camera* camera = new Camera(glm::vec3(1.5f, 2.0f, 3.0f),glm::vec3(0.0f, 1.0f, 0.0f),-120.0f,-28.0f);
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;



	glm::mat4 model;

	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)win_width / (float)win_height, 0.1f, 100.0f);

	// 渲染循环
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


		glm::mat4 view = camera->GetViewMatrix();

		double time = glfwGetTime();
		lightPos = glm::vec3(1.0f * sin(time), 0.8 + 0.2f * sin(time * 7.0f), 1.0f * cos(time));
		//lightPos = glm::vec3(0.1f, 1.0f, 2.0f);
		glm::mat4 modelLight;
		modelLight = glm::translate(modelLight, lightPos);
		modelLight = glm::scale(modelLight, glm::vec3(0.05,0.1,0.05));


		// LIGHT
		shaderLight->use();
		shaderLight->setMat4("model", glm::value_ptr(modelLight));
		shaderLight->setMat4("view", glm::value_ptr(view));
		shaderLight->setMat4("projection", glm::value_ptr(projection));
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0,36);



		// OBJECT
		shader->use();
		shader->setMat4("model", glm::value_ptr(model));
		shader->setMat4("view", glm::value_ptr(view));
		shader->setMat4("projection", glm::value_ptr(projection));

		glm::vec3 lightColor = glm::vec3(1.0,1.0,1.0);

		// light properties
		shader->setVec3("light.ambient", glm::vec3(1.0f, 1.0f, 1.0f)); // note that all light colors are set at full intensity
		shader->setVec3("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		// material properties
		shader->setVec3("material.ambient", ambient);
		shader->setVec3("material.diffuse", diffuse);
		shader->setVec3("material.specular", specular);
		shader->setFloat("material.shininess", shininess);

		shader->setVec3("light.position", glm::value_ptr(lightPos));
		shader->setVec3("viewPos", glm::value_ptr(camera->Position));

		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0,36);


		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete shader;
	delete shaderLight;
	delete camera;

	return 0;

}


// 金箱子
int goldenBox(GLFWwindow* window)
{
	return boxWithMaterial(window,
		glm::vec3(0.247250, 0.199500, 0.074500),
		glm::vec3(0.751640, 0.606480, 0.226480), 
		glm::vec3(0.628281, 0.555802, 0.366065),
		51.200001);
}


// 银箱子
int silverBox(GLFWwindow* window)
{
	return boxWithMaterial(window,
		glm::vec3(0.231250, 0.231250, 0.231250),
		glm::vec3(0.277500, 0.277500, 0.277500), 
		glm::vec3(0.773911, 0.773911, 0.773911),
		89.599998);
}


// 橡胶箱子
int rubberBox(GLFWwindow* window)
{
	return boxWithMaterial(window,
		glm::vec3(0.020000, 0.020000, 0.020000),
		glm::vec3(0.010000, 0.010000, 0.010000), 
		glm::vec3(0.400000, 0.400000, 0.400000),
		10.000000);
}

