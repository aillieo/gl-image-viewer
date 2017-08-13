#pragma once

#include "../Utils/GLMethod.h"

// 渲染到纹理
int RenderToTexture(GLFWwindow* window);

// 四种后处理
int postProcessings(GLFWwindow* window);

// 在模板测试中使用渲染缓冲对象
int stencilTestingWithRBO(GLFWwindow* window);
