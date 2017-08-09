#include "StencilTesting.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"


// ����ֻ��ʾָ������
int simpleClip(GLFWwindow* window)
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	int win_width,win_height;
	glfwGetWindowSize(window,&win_width,&win_height);


	Shader* shader = new Shader("StencilTesting/shader2.vsh","StencilTesting/shader2.fsh");
	Shader* shaderStencil = new Shader("StencilTesting/shader1.vsh","StencilTesting/shader1.fsh");

	float cubeVertices[] = {
		// x  y  z    s  t	
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

	// stencil vertex array
	float stencilVertices[] = {
		-0.9f,  0.0f, 0.0f,
		0.0f,  0.0f, 0.0f,
		-0.6f, -0.3f, 0.0f,
		-0.3f, -0.3f, 0.0f,
		-0.6f, -0.6f, 0.0f,
		-0.3f, -0.6f, 0.0f,
		-0.9f, -0.9f, 0.0f,
		0.0f, -0.9f, 0.0f
	}; 


	// stencil indices array
	unsigned int stencilIndices[] = {
		0,1,2,
		1,2,3,
		0,2,4,
		0,4,6,
		1,3,5,
		1,5,7,
		4,6,7,
		4,5,7
	};


	// bind VAO VBO
	unsigned int VBO[3], VAO[3], EBO;
	glGenVertexArrays(3, VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(3, VBO);


	// for cube
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// for plane
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// for stencil
	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(stencilVertices), stencilVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stencilIndices), stencilIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
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


		// ����
		processInput(window);
		processInput(window, camera, deltaTime);

		// ��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


		// stencil
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); 
		glStencilFunc(GL_ALWAYS, 1, 0xFF); // ����д��ģ�建��
		glStencilMask(0xFF);

		shaderStencil->use();
		glBindVertexArray(VAO[2]);

		
		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

		glStencilMask(0x00); 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); //��Ҫ��Ϊ�˰ѻ��Ƴ�����ģ������� ������ģ�建�� [�������ķ���]

		// ------------------------------------------------------------


		glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
		shader->use();
		glm::mat4 model;
		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera->Zoom, (float)win_width / (float)win_height, 0.1f, 100.0f);
		shader->setMat4("view", view);
		shader->setMat4("projection", projection);

		// two cubes
		glBindVertexArray(VAO[0]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureCube); 	
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		shader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		shader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// floor
		glBindVertexArray(VAO[1]);
		glBindTexture(GL_TEXTURE_2D, texturePlane);
		shader->setMat4("model", glm::mat4());
		glDrawArrays(GL_TRIANGLES, 0, 6);



		glBindVertexArray(0);


		// ��鲢�����¼�����������
		glfwPollEvents();
		glfwSwapBuffers(window);
	}




	glDeleteVertexArrays(3, VAO);
	glDeleteBuffers(3, VBO);
	glDeleteBuffers(1, &EBO);

	unbindCamera(window);

	delete shader;
	delete shaderStencil;
	delete camera;

	return 0;

}

// �����Ӽ�����
int boxOutlining(GLFWwindow* window)
{

    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    
    int win_width,win_height;
    glfwGetWindowSize(window,&win_width,&win_height);
    
    
    Shader* shader = new Shader("StencilTesting/shader2.vsh","StencilTesting/shader2.fsh");
    Shader* shaderOutline = new Shader("StencilTesting/shader3.vsh","StencilTesting/shader3.fsh");
    
    float cubeVertices[] = {
        // x  y  z    s  t
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
    
    
    // for cube
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // for plane
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    
    
    
    // load texture
    glActiveTexture(GL_TEXTURE0);
    unsigned int textureCube = TextureLoader::loadTexture("lighting_maps/diffuseMap.png");
    glActiveTexture(GL_TEXTURE1);
    unsigned int texturePlane = TextureLoader::loadTexture("lighting_maps/specularMap.png");
    
    
    
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f),-90.0,0.0f);
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    bindCameraToWindow(window, camera);
    
    
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // ����д��ģ�建��
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // ���ͨ��������дΪref��ֵ �˴���1
    
    
    while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        
        // ����
        processInput(window);
        processInput(window, camera, deltaTime);
        
        // ��Ⱦָ��
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        
        // MVP
        glm::mat4 model;
        glm::mat4 view = camera->GetViewMatrix();
        glm::mat4 projection = glm::perspective(camera->Zoom, (float)win_width / (float)win_height, 0.1f, 100.0f);
        
        
        
        glStencilFunc(GL_ALWAYS, 1, 0xFF); // ����д��ģ�建��
        
        
        // �Ȼ������ӱ���
        // ��ʱ����ģ�建��д��
        glStencilMask(0xFF); // ����д��
        
        
        shader->use();
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        
        
        glBindVertexArray(VAO[0]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureCube);
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        shader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        shader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        

        glStencilMask(0x00);  // ģ�建���ֹд��
        
        // �ذ�
        glBindVertexArray(VAO[1]);
        glBindTexture(GL_TEXTURE_2D, texturePlane);
        shader->setMat4("model", glm::mat4());
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        
        // ���ӵ�����
        // ��ʱ��Ҫģ�����
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);

        
        // ���ҹر���Ȳ���
        glDisable(GL_DEPTH_TEST);
        
        shaderOutline->use();
        shaderOutline->setMat4("view", view);
        shaderOutline->setMat4("projection", projection);
        
        
        glBindVertexArray(VAO[0]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureCube);
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
        shaderOutline->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model = glm::mat4();
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
        shaderOutline->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        

        glStencilMask(0xFF);// ������ ��һ��ȥ���ͻᵼ��outline���Ʋ����� �������Ʋ�û�н���
        
        glEnable(GL_DEPTH_TEST);
        glBindVertexArray(0);
        
        
        // ��鲢�����¼�����������
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    
    
    
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    
    unbindCamera(window);
    
    delete shader;
    delete shaderOutline;
    delete camera;
    
    return 0;
}

