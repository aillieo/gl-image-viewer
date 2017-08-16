#pragma once

#include "../Utils/GLMethod.h"


// 错误的天空盒（不控制model位移）
int badSkyBox(GLFWwindow* window);

// 正确的天空盒
int rightSkyBox(GLFWwindow* window);

// 立方体反射
int boxReflection(GLFWwindow* window);

// 模型反射
int modelReflection(GLFWwindow* window);

// 立方体折射
int boxRefraction(GLFWwindow* window);

// 模型折射
int modelRefraction(GLFWwindow* window);
