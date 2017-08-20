#pragma once


#include "../Utils/GLMethod.h"

// 在几何着色器中把点变成线
int gshPointToLine(GLFWwindow* window);

// 在几何着色器中把点变成“房子”
int gshPointToHouse(GLFWwindow* window);

// 在几何着色器中把点变成不同颜色的“房子”
int gshPointToHouseColor(GLFWwindow* window);

// 在几何着色器中把点变成带白色顶部的不同颜色的“房子”
int gshPointToHouseColorWithWhite(GLFWwindow* window);
