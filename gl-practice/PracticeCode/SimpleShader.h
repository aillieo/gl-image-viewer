#pragma once

#include "../Utils/GLMethod.h"

// 使用Shader类
int useShaderClass(GLFWwindow* window);

// vsh输出颜色
int colorFromVSH(GLFWwindow* window);

// 变色
int changeColorByUniform(GLFWwindow* window);

// 变位置
int changePosByUniform(GLFWwindow* window);

// 向VBO写入颜色
int triangleColorVBO(GLFWwindow* window);

