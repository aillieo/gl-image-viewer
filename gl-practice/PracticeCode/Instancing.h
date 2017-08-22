#pragma once


#include "../Utils/GLMethod.h"

// 阵列 不使用Instancing
int arrayWithoutInstancing(GLFWwindow* window);

// 阵列 使用Instancing
int arrayWithInstancing(GLFWwindow* window);

// 阵列 使用Instancing 尺寸渐变
int arrayWithInstancingScaling(GLFWwindow* window);

// 行星带 不使用Instancing
int asteroidFieldWithoutInstancing(GLFWwindow* window);

// 行星带 使用Instancing
int asteroidFieldWithInstancing(GLFWwindow* window);

