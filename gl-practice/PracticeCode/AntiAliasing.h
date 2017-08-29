#pragma once


#include "../Utils/GLMethod.h"

// 不使用抗锯齿
int cubeWithoutAA(GLFWwindow* window);

// 使用多重采样抗锯齿
int cubeWithMSAA(GLFWwindow* window);

// 使用离屏多重采样抗锯齿
int cubeWithOffScreenMSAA(GLFWwindow* window);

// 使用自定义抗锯齿算法
int cubeCustomAAAlgorithm(GLFWwindow* window);

