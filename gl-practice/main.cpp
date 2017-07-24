#include "Utils/GLMethod.h"
#include "SceneManager.h"

#include "PracticeCode/HelloTriangle.h"
#include "PracticeCode/SimpleShader.h"
#include "PracticeCode/SimpleTexture.h"
#include "PracticeCode/SimpleTransform.h"


int main()  
{  

	GLFWwindow* window = createWindow();
	if(nullptr == window)
	{
		return -1;
	}

	//
	SceneManager::sceneIndexMax = 17;


	while (!glfwWindowShouldClose(window))
	{

		SceneManager::willChangeScene = false;

		switch (SceneManager::index)
		{
		case 0:
			// ����һ��������
			drawHelloTriangleVAO(window);
			break;
		case 1:
			// �������������� ��ʹ��EBO
			drawTwoTriangleNoEBO(window);
			break;
		case 2:
			// �������������� ��ʹ��EBO
			drawTwoTriangleEBO(window);
			break;
		case 3:
			// �������������� �ֱ�ʹ������VAO
			drawTwoTriangleTwoVAO(window);
			break;
		case 4:
			// �������������� ʹ�ò�ͬ��shader ʹ����ɫ��ͬ
			drawHelloTriangleTwoShader(window);
			break;
		case 5:
			// �������������� ʹ�ò�ͬ��shader ʹ����ɫ��ͬ ��ʹ��EBO
			drawHelloTriangleTwoShaderEBO(window);
			break;
		case 6:
			// ʹ��Shader��
			useShaderClass(window);
			break;
		case 7:
			// vsh�����ɫ
			colorFromVSH(window);
			break;
		case 8:
			// ��ɫ
			changeColorByUniform(window);
			break;
		case 9:
			// ��λ��
			changePosByUniform(window);
			break;
		case 10:
			// ��VBOд����ɫ
			triangleColorVBO(window);
			break;
		case 11:
			// �������μ�������
			textureForTriangle(window);
			break;
		case 12:
			// ��ʾͼƬ
			displayImage(window);
			break;
		case 13:
			// gray
			grayImage(window);
			break;
		case 14:
			// ����ɫ���ĸ�ͼƬ
			fourImages(window);
			break;
		case 15:
			// ����������
			twoTextureMix(window);
			break;
		case 16:
			// ���ֲ�ͬ������ʽ�Ŵ�
			magnifyTextures(window);
			break;
		case 17:
			// ƽ������ת
			rotate2D(window);
				break;
		default:
			break;
		}
		
	}
	

	glfwTerminate();

	return 0;

}


