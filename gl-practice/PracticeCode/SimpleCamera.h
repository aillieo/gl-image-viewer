#pragma once

#include "../Utils/GLMethod.h"

// 用view矩阵旋转摄像机
int cameraRotateView(GLFWwindow* window);

// 用lookat旋转摄像机
int cameraRotateLookAt(GLFWwindow* window);

// ASDW控制摄像机
int cameraControl(GLFWwindow* window);

