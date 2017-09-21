#pragma once


#include "../Utils/GLMethod.h"

// 不使用HDR
int lightWithoutHDR(GLFWwindow* window);

// HDR reinhard算法
int HDRWithReinhard(GLFWwindow* window);

// HDR 高曝光
int HDRWithHighExposure(GLFWwindow* window);

// HDR 低曝光
int HDRWithLowExposure(GLFWwindow* window);


