#include "AntiAliasing.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"
#include "../Utils/Model.h"

// ��ʹ�ÿ����
int cubeWithoutAA(GLFWwindow* window)
{

	return 0;
}

// ʹ�ö��ز��������
int cubeWithMSAA(GLFWwindow* window)
{

	return 0;
}

// ʹ���������ز��������
int cubeWithOffScreenMSAA(GLFWwindow* window)
{

	return 0;
}

// ʹ���Զ��忹����㷨
int cubeCustomAAAlgorithm(GLFWwindow* window)
{

	return 0;
}

