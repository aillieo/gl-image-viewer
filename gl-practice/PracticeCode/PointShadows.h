#pragma once


#include "../Utils/GLMethod.h"

// ���Ƶ��Դ����Ӱ
int renderPointShadow(GLFWwindow* window);

// չʾ���Դ��Ӱ�������ͼ
int renderPointShadowShowDepth(GLFWwindow* window);

// ���Ƶ��Դ��Ӱ��ʹ��PCF
int renderPointShadowPCF(GLFWwindow* window);
