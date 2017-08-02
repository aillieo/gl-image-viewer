#include "LightCasters.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"

#include "../SceneManager.h"
#include "../Utils/TextureLoader.h"


int directionalLight(GLFWwindow* window)
{
	// 开启深度检测
	glEnable(GL_DEPTH_TEST);

	int win_width,win_height;
	glfwGetWindowSize(window,&win_width,&win_height);



	// SHADER
	Shader* shader = new Shader("LightCasters/shader2.vsh","LightCasters/shader2.fsh");


	// VERTICES:
	// x, y, z, x, y, z, s, t
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};



	// bind VAO VBO
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);







    glActiveTexture(GL_TEXTURE0);
    unsigned int diffuseMap = TextureLoader::loadTexture("lighting_maps/diffuseMap.png");
    
    glActiveTexture(GL_TEXTURE1);
    unsigned int specularMap = TextureLoader::loadTexture("lighting_maps/specularMap.png");




	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f),glm::vec3(0.0f, 1.0f, 0.0f),-90.0,0.0f);
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;


	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};

	glm::vec3 lightDir =  glm::vec3(-1.5f, -0.0f, -0.5f);

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



		// OBJECT
		for (int i = 0; i < sizeof(cubePositions)/sizeof(cubePositions[0]); i++)
		{
			shader->use();
			
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() + i, glm::vec3(0.1f * (i % 5), - 0.2f * (i % 3), 0.0f));

			
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
			//shader->setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
			shader->setInt("material.diffuse", 0);
			shader->setInt("material.specular", 1);
			shader->setFloat("material.shininess", 32.0f);

	
			shader->setVec3("light.direction", lightDir);
			shader->setVec3("viewPos", glm::value_ptr(camera->Position));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuseMap);

			glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			glDrawArrays(GL_TRIANGLES, 0,36);

		}

		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete shader;
	delete camera;

	return 0;
}



// 点光源
int pointLight(GLFWwindow* window)
{
    // 开启深度检测
    glEnable(GL_DEPTH_TEST);
    
    int win_width,win_height;
    glfwGetWindowSize(window,&win_width,&win_height);
    
    
    
    // SHADER
    Shader* shaderLight = new Shader("LightCasters/shader1.vsh","LightCasters/shader1.fsh");
    Shader* shader = new Shader("LightCasters/shader3.vsh","LightCasters/shader3.fsh");
    
    
    // VERTICES:
    // x, y, z, x, y, z, s, t
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    
    
    
    // bind VAO VBO
    unsigned int VBO, VAO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
    
    
    
    
    
    
    glActiveTexture(GL_TEXTURE0);
    unsigned int diffuseMap = TextureLoader::loadTexture("lighting_maps/diffuseMap.png");
    
    glActiveTexture(GL_TEXTURE1);
    unsigned int specularMap = TextureLoader::loadTexture("lighting_maps/specularMap.png");
    
    
    
    
    glm::vec3 lightPos;
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f),glm::vec3(0.0f, 1.0f, 0.0f),-90.0,0.0f);
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    
    
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };
    
    
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
        lightPos = glm::vec3(1.5f, 0.0f, 0.5f);
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
        for (int i = 0; i < sizeof(cubePositions)/sizeof(cubePositions[0]); i++)
        {
            shader->use();
            
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime() + i, glm::vec3(0.1f * (i % 5), - 0.2f * (i % 3), 0.0f));
            
            
            shader->setMat4("model", glm::value_ptr(model));
            shader->setMat4("view", glm::value_ptr(view));
            shader->setMat4("projection", glm::value_ptr(projection));
            
            glm::vec3 lightColor = glm::vec3(1.0,1.0,1.0);
            
            glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
            glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
            shader->setVec3("light.ambient", ambientColor);
            shader->setVec3("light.diffuse", diffuseColor);
            shader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
            
            //距离=50时的参数：
            shader->setFloat("light.constant",  1.0f);
            shader->setFloat("light.linear",    0.09f);
            shader->setFloat("light.quadratic", 0.032f);
            
            //距离=20时的参数：
            //shader->setFloat("light.constant",  1.0f);
            //shader->setFloat("light.linear",    0.22f);
            //shader->setFloat("light.quadratic", 0.20f);
            
            
            // material properties
            //shader->setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
            shader->setInt("material.diffuse", 0);
            shader->setInt("material.specular", 1);
            shader->setFloat("material.shininess", 32.0f);
            
            
            shader->setVec3("light.position", lightPos);
            shader->setVec3("viewPos", glm::value_ptr(camera->Position));
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap);
            
            glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(GL_TRIANGLES, 0,36);
            
        }
        
        
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

// 聚光灯
int spotlight(GLFWwindow* window)
{
    // 开启深度检测
    glEnable(GL_DEPTH_TEST);
    
    int win_width,win_height;
    glfwGetWindowSize(window,&win_width,&win_height);
    
    
    
    // SHADER
    Shader* shaderLight = new Shader("LightCasters/shader1.vsh","LightCasters/shader1.fsh");
    Shader* shader = new Shader("LightCasters/shader4.vsh","LightCasters/shader4.fsh");
    
    
    // VERTICES:
    // x, y, z, x, y, z, s, t
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    
    
    
    // bind VAO VBO
    unsigned int VBO, VAO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
    
    
    
    
    
    
    glActiveTexture(GL_TEXTURE0);
    unsigned int diffuseMap = TextureLoader::loadTexture("lighting_maps/diffuseMap.png");
    
    glActiveTexture(GL_TEXTURE1);
    unsigned int specularMap = TextureLoader::loadTexture("lighting_maps/specularMap.png");
    
    
    
    
    
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f),glm::vec3(0.0f, 1.0f, 0.0f),-90.0,0.0f);
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    
    
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    
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
        glm::vec3 lightPos = glm::vec3(1.5f, 0.0f, 0.5f);
        glm::vec3 lightDir = glm::vec3(-1.5f, 0.0f, -0.5f);
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
        for (int i = 0; i < sizeof(cubePositions)/sizeof(cubePositions[0]); i++)
        {
            shader->use();
            
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime() + i, glm::vec3(0.1f * (i % 5), - 0.2f * (i % 3), 0.0f));
            
            
            shader->setMat4("model", glm::value_ptr(model));
            shader->setMat4("view", glm::value_ptr(view));
            shader->setMat4("projection", glm::value_ptr(projection));
            
            glm::vec3 lightColor = glm::vec3(1.0,1.0,1.0);
            
            glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
            glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
            shader->setVec3("light.ambient", ambientColor);
            shader->setVec3("light.diffuse", diffuseColor);
            shader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
            
            // spotlight
            shader->setFloat("light.cutOff", glm::cos(glm::radians(9.5f)));
            shader->setFloat("light.outerCutOff", glm::cos(glm::radians(11.5f)));
            
            // attenuation
            // for distance = 3250
            shader->setFloat("light.constant",  1.0f);
            shader->setFloat("light.linear",    0.0014f);
            shader->setFloat("light.quadratic", 0.000007f);
            
            // material properties
            //shader->setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
            shader->setInt("material.diffuse", 0);
            shader->setInt("material.specular", 1);
            shader->setFloat("material.shininess", 32.0f);
            
            //shader->setVec3("light.direction", lightDir);
            //shader->setVec3("light.position", lightPos);
            shader->setVec3("light.direction", camera->Front);
            shader->setVec3("light.position", camera->Position);
            shader->setVec3("viewPos", glm::value_ptr(camera->Position));
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap);
            
            glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(GL_TRIANGLES, 0,36);
            
        }
        
        
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

