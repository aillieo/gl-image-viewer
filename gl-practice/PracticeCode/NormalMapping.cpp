#include "NormalMapping.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"

// 法线贴图 将TBN传给片段着色器
int normalMappingTBN1(GLFWwindow* window)
{

	return 0;
}


// 法线贴图 在片段着色器中使用切线空间计算光照
int normalMappingTBN2(GLFWwindow* window)
{

	return 0;
}

