#pragma once

#include "../Utils/GLMethod.h"

// ��Ⱦ������
int RenderToTexture(GLFWwindow* window);

// ���ֺ���
int postProcessings(GLFWwindow* window);

// ��ģ�������ʹ����Ⱦ�������
int stencilTestingWithRBO(GLFWwindow* window);
