#pragma once

// ����һ��������
int drawHelloTriangleVAO(GLFWwindow* window);

// �������������� ��ʹ��EBO
int drawTwoTriangleNoEBO(GLFWwindow* window);

// �������������� ��ʹ��EBO
int drawTwoTriangleEBO(GLFWwindow* window);

// �������������� �ֱ�ʹ������VAO
int drawTwoTriangleTwoVAO(GLFWwindow* window);

// �������������� ʹ�ò�ͬ��shader ʹ����ɫ��ͬ
int drawHelloTriangleTwoShader(GLFWwindow* window);

// �������������� ʹ�ò�ͬ��shader ʹ����ɫ��ͬ ��ʹ��EBO
int drawHelloTriangleTwoShaderEBO(GLFWwindow* window);