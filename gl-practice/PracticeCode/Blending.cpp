#include "Blending.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"


// Ƭ����ɫ���ж���͸��Ƭ��
int discardFragAlpha(GLFWwindow* window)
{
	return 0;
}

// ��˳�����͸������
int transparentWithSorting(GLFWwindow* window)
{
	return 0;
}
