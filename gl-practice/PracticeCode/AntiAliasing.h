#pragma once


#include "../Utils/GLMethod.h"

// ��ʹ�ÿ����
int cubeWithoutAA(GLFWwindow* window);

// ʹ�ö��ز��������
int cubeWithMSAA(GLFWwindow* window);

// ʹ���������ز�������� ���Ƶ�frameBuffer��blit����Ļ
int cubeWithOffScreenMSAA(GLFWwindow* window);

// ʹ���������ز�������� ͨ��֡��������
int cubeWithOffScreenMSAATexture(GLFWwindow* window);

// ʹ���Զ��忹����㷨
int cubeCustomAAAlgorithm(GLFWwindow* window);

