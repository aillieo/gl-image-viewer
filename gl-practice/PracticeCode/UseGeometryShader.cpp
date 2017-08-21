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

// �ڼ�����ɫ���аѵ�����
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



	// ��Ⱦѭ��
	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{
		// ����
		processInput(window);

		// ��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		shader->use();
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_POINTS, 0, 3);


		// ��鲢�����¼�����������
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete shader;


	return 0; 


}

// �ڼ�����ɫ���аѵ��ɡ����ӡ�
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



	// ��Ⱦѭ��
	while(!glfwWindowShouldClose(window) && !SceneManager::willChangeScene)
	{
		// ����
		processInput(window);

		// ��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		shader->use();
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_POINTS, 0, 3);


		// ��鲢�����¼�����������
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete shader;


	return 0; 


}

// �ڼ�����ɫ���аѵ��ɲ�ͬ��ɫ�ġ����ӡ�
int gshPointToHouseColor(GLFWwindow* window)
{
    return 0;
}

// �ڼ�����ɫ���аѵ��ɴ���ɫ�����Ĳ�ͬ��ɫ�ġ����ӡ�
int gshPointToHouseColorWithWhite(GLFWwindow* window)
{
    return 0;
}

// ʹ����ɫ�����챬ըЧ��
int gshExplode(GLFWwindow* window)
{
    return 0;
}

// ʹ����ɫ����ʾ����
int gshDisplayNormals(GLFWwindow* window)
{
    return 0;
}
