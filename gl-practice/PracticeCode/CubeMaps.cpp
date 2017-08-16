#include "CubeMaps.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"


// 错误的天空盒（不控制view位移）
int badSkyBox(GLFWwindow* window)
{

	return 0;
}

// 正确的天空盒
int rightSkyBox(GLFWwindow* window)
{

	return 0;
}
// 立方体反射
int boxReflection(GLFWwindow* window)
{

	return 0;
}

// 模型反射
int modelReflection(GLFWwindow* window)
{

	return 0;
}

// 立方体折射
int boxRefraction(GLFWwindow* window)
{

	return 0;
}

// 模型折射
int modelRefraction(GLFWwindow* window)
{

	return 0;
}
