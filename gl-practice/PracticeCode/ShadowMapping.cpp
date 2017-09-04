#include "ShadowMapping.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"
#include "../Utils/TextureLoader.h"
#include "../Utils/Camera.h"

#include "../SceneManager.h"

// 用于绘制阴影的深度可视化
int depthMapForShadow(GLFWwindow* window)
{
    
    return 0;
}

// 绘制阴影-1 初步实现
int renderingShadow1Raw(GLFWwindow* window)
{
    
    return 0;
}

// 绘制阴影-2 使用偏移减少阴影失真
int renderingShadow2Bias(GLFWwindow* window)
{
    
    return 0;
}

// 绘制阴影-3 使用面剔除剔除正面 以避免悬浮
int renderingShadow3CullFront(GLFWwindow* window)
{
    
    return 0;
}

// 绘制阴影-4 使用shader中增加判断 以避免采样过多over-sampling
int renderingShadow4FixOverSampling(GLFWwindow* window)
{
    
    return 0;
}

// 绘制阴影-final 使用PCF(percentage-closer filtering)
int renderingShadowsWithPCF(GLFWwindow* window)
{
    
    return 0;
}

