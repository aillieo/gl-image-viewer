#pragma once


#include "../Utils/GLMethod.h"

// 用于绘制阴影的深度可视化
int depthMapForShadow(GLFWwindow* window);

// 绘制阴影-1 初步实现
int renderingShadow1Raw(GLFWwindow* window);

// 绘制阴影-2 使用偏移减少阴影失真
int renderingShadow2Bias(GLFWwindow* window);

// 绘制阴影-3 使用面剔除剔除正面 以避免悬浮(peter panning)
int renderingShadow3CullFront(GLFWwindow* window);

// 绘制阴影-4 修改texture边界类型并在shader中增加判断 以避免采样过多over-sampling
int renderingShadow4FixOverSampling(GLFWwindow* window);

// 绘制阴影-final 使用PCF(percentage-closer filtering)
int renderingShadowsWithPCF(GLFWwindow* window);

