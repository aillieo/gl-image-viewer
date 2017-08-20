#include "UseGeometryShader.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"
#include "../Utils/Model.h"

// 在几何着色器中把点变成线
int gshPointToLine(GLFWwindow* window)
{
    return 0;
}

// 在几何着色器中把点变成“房子”
int gshPointToHouse(GLFWwindow* window)
{
    return 0;
}

// 在几何着色器中把点变成不同颜色的“房子”
int gshPointToHouseColor(GLFWwindow* window)
{
    return 0;
}

// 在几何着色器中把点变成带白色顶部的不同颜色的“房子”
int gshPointToHouseColorWithWhite(GLFWwindow* window)
{
    return 0;
}
