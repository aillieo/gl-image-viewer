#include "AdvancedGLSL.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"
#include "../Utils/Model.h"

// 使用gl_PointSize
int usePointSize(GLFWwindow* window)
{

	return 0;
}

// 使用gl_FragCoord
int useFragCoord(GLFWwindow* window)
{

	return 0;
}

// 使用gl_FrontFacing
int useFrontFacing(GLFWwindow* window)
{

	return 0;
}

// 使用UBO uniform buffer object
int useUBO(GLFWwindow* window)
{

	return 0;
}