#include "Instancing.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"
#include "../Utils/Model.h"

// 阵列 不使用Instancing
int arrayWithoutInstancing(GLFWwindow* window)
{

	return 0;
}

// 阵列 使用Instancing
int arrayWithInstancing(GLFWwindow* window)
{

	return 0;
}

// 阵列 使用Instancing 尺寸渐变
int arrayWithInstancingScaling(GLFWwindow* window)
{

	return 0;
}

// 行星带 不使用Instancing
int asteroidFieldWithoutInstancing(GLFWwindow* window)
{

	return 0;
}

// 行星带 使用Instancing
int asteroidFieldWithInstancing(GLFWwindow* window)
{

	return 0;
}


