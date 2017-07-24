#pragma once

#include "../Utils/GLMethod.h"

// 给三角形加上纹理
int textureForTriangle(GLFWwindow* window);

// 显示图片
int displayImage(GLFWwindow* window);


// gray
int grayImage(GLFWwindow* window);


// 带颜色的四个图片
int fourImages(GLFWwindow* window);


// 两张纹理混合
int twoTextureMix(GLFWwindow* window);


// 两种不同采样方式放大
int magnifyTextures(GLFWwindow* window);

