#include "ShadowMapping.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"

// ���ڻ�����Ӱ����ȿ��ӻ�
int depthMapForShadow(GLFWwindow* window)
{
    
    return 0;
}

// ������Ӱ-1 ����ʵ��
int renderingShadow1Raw(GLFWwindow* window)
{
    
    return 0;
}

// ������Ӱ-2 ʹ��ƫ�Ƽ�����Ӱʧ��
int renderingShadow2Bias(GLFWwindow* window)
{
    
    return 0;
}

// ������Ӱ-3 ʹ�����޳��޳����� �Ա�������
int renderingShadow3CullFront(GLFWwindow* window)
{
    
    return 0;
}

// ������Ӱ-4 ʹ��shader�������ж� �Ա����������over-sampling
int renderingShadow4FixOverSampling(GLFWwindow* window)
{
    
    return 0;
}

// ������Ӱ-final ʹ��PCF(percentage-closer filtering)
int renderingShadowsWithPCF(GLFWwindow* window)
{
    
    return 0;
}

