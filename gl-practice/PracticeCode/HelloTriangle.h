#pragma once

// 绘制一个三角形
int drawHelloTriangleVAO(GLFWwindow* window);

// 绘制两个三角形 不使用EBO
int drawTwoTriangleNoEBO(GLFWwindow* window);

// 绘制两个三角形 并使用EBO
int drawTwoTriangleEBO(GLFWwindow* window);

// 绘制两个三角形 分别使用两个VAO
int drawTwoTriangleTwoVAO(GLFWwindow* window);

// 绘制两个三角形 使用不同的shader 使其颜色不同
int drawHelloTriangleTwoShader(GLFWwindow* window);

// 绘制两个三角形 使用不同的shader 使其颜色不同 并使用EBO
int drawHelloTriangleTwoShaderEBO(GLFWwindow* window);