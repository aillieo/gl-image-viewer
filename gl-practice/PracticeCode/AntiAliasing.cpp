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

// 不使用抗锯齿
int cubeWithoutAA(GLFWwindow* window)
{

	return 0;
}

// 使用多重采样抗锯齿
int cubeWithMSAA(GLFWwindow* window)
{

	return 0;
}

// 使用离屏多重采样抗锯齿
int cubeWithOffScreenMSAA(GLFWwindow* window)
{

	return 0;
}

// 使用自定义抗锯齿算法
int cubeCustomAAAlgorithm(GLFWwindow* window)
{

	return 0;
}

