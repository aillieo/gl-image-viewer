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

// �ڼ�����ɫ���аѵ�����
int gshPointToLine(GLFWwindow* window)
{
    return 0;
}

// �ڼ�����ɫ���аѵ��ɡ����ӡ�
int gshPointToHouse(GLFWwindow* window)
{
    return 0;
}

// �ڼ�����ɫ���аѵ��ɲ�ͬ��ɫ�ġ����ӡ�
int gshPointToHouseColor(GLFWwindow* window)
{
    return 0;
}

// �ڼ�����ɫ���аѵ��ɴ���ɫ�����Ĳ�ͬ��ɫ�ġ����ӡ�
int gshPointToHouseColorWithWhite(GLFWwindow* window)
{
    return 0;
}
