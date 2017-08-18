#pragma once


#include "../Utils/GLMethod.h"

// 使用gl_PointSize
int usePointSize(GLFWwindow* window);

// 使用gl_FragCoord
int useFragCoord(GLFWwindow* window);

// 使用gl_FrontFacing
int useFrontFacing(GLFWwindow* window);

// 使用UBO uniform buffer object
int useUBO(GLFWwindow* window);
