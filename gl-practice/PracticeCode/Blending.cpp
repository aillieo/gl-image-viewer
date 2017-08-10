#include "Blending.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"


// 片段着色器中丢弃透明片段
int discardFragAlpha(GLFWwindow* window)
{
	return 0;
}

// 按顺序绘制透明物体
int transparentWithSorting(GLFWwindow* window)
{
	return 0;
}
