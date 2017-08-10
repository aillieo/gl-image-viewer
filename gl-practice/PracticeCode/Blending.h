#pragma once

#include "../Utils/GLMethod.h"

// 片段着色器中丢弃透明片段
int discardFragAlpha(GLFWwindow* window);

// 按顺序绘制透明物体
int transparentWithSorting(GLFWwindow* window);

