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

// ʹ��gl_PointSize
int usePointSize(GLFWwindow* window)
{

	return 0;
}

// ʹ��gl_FragCoord
int useFragCoord(GLFWwindow* window)
{

	return 0;
}

// ʹ��gl_FrontFacing
int useFrontFacing(GLFWwindow* window)
{

	return 0;
}

// ʹ��UBO uniform buffer object
int useUBO(GLFWwindow* window)
{

	return 0;
}