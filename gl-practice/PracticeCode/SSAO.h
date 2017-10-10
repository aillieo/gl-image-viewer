#pragma once


#include "../Utils/GLMethod.h"

// SSAO着色器
int SSAOShader(GLFWwindow* window);

// SSAO模糊
int SSAOBlur(GLFWwindow* window);

// SSAO 增加了一个光源
int SSAOAndLight(GLFWwindow* window);