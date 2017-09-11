#pragma once


#include "../Utils/GLMethod.h"

// 绘制点光源的阴影
int renderPointShadow(GLFWwindow* window);

// 展示点光源阴影的深度贴图
int renderPointShadowShowDepth(GLFWwindow* window);

// 绘制点光源阴影并使用PCF
int renderPointShadowPCF(GLFWwindow* window);
