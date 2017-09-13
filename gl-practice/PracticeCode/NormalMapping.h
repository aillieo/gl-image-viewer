#pragma once


#include "../Utils/GLMethod.h"

// 法线贴图 将TBN传给片段着色器
int normalMappingTBN1(GLFWwindow* window);

// 法线贴图 在片段着色器中使用切线空间计算光照
int normalMappingTBN2(GLFWwindow* window);