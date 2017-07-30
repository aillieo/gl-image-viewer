#include "Utils/GLMethod.h"
#include "SceneManager.h"

#include "PracticeCode/HelloTriangle.h"
#include "PracticeCode/SimpleShader.h"
#include "PracticeCode/SimpleTexture.h"
#include "PracticeCode/SimpleTransform.h"
#include "PracticeCode/SimpleTransform3D.h"
#include "PracticeCode/SimpleCamera.h"
#include "PracticeCode/BasicLighting.h"
#include "PracticeCode/BasicMaterials.h"



int main()  
{  

	GLFWwindow* window = createWindow();
	if(nullptr == window)
	{
		return -1;
	}

	//
	SceneManager::sceneIndexMax = 30;
	SceneManager::index = SceneManager::sceneIndexMax;

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
		case 18:
			// ƽ��������ת
			moveScaleRotate(window);
			break;
		case 19:
			// ƽ��������ת
			box3D(window);
			break;
		case 20:
            // ����ռ���ת
            rotate3DMulti(window);
            break;
		case 21:
			// ��view������ת�����
			cameraRotateView(window);
			break;
		case 22:
			// ��lookat��ת�����
			cameraRotateLookAt(window);
			break;
		case 23:
			// ASDW���������
			cameraControl(window);
			break;
		case 24:
			// ����ɫ������������Դ û��ʹ�ù���
			noLighting(window);
			break;
		case 25:
			// ֻ�л�����
			ambientAlone(window);
			break;
		case 26:
			// ֻ��������
			diffuseAlone(window);
			break;
		case 27:
			// ֻ�о��淴��
			specularAlone(window);
			break;
		case 28:
			// ʹ��Phong����ģ��
			PhongLighting(window);
			break;
		case 29:
			// ʹ��Phong����ģ�� �˶��Ĺ�Դ
			PhongLightingMoving(window);
			break;
        case 30:
            // ʹ�ò���
            useMaterials(window);
            break;
		default:
			break;
		}
	}

	glfwTerminate();

	return 0;

}


