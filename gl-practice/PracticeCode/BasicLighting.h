#pragma once

#include "../Utils/GLMethod.h"

// 带颜色的物体和虚拟光源 没有使用光照
int noLighting(GLFWwindow* window);

// 只有环境光
int ambientAlone(GLFWwindow* window);

// 只有漫反射
int diffuseAlone(GLFWwindow* window);

// 只有镜面反射
int specularAlone(GLFWwindow* window);

// 使用Phong光照模型
int PhongLighting(GLFWwindow* window);

