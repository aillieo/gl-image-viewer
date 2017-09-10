#pragma once


#include "../Utils/GLMethod.h"

// ���ڻ�����Ӱ����ȿ��ӻ�
int depthMapForShadow(GLFWwindow* window);

// ������Ӱ-1 ����ʵ��
int renderingShadow1Raw(GLFWwindow* window);

// ������Ӱ-2 ʹ��ƫ�Ƽ�����Ӱʧ��
int renderingShadow2Bias(GLFWwindow* window);

// ������Ӱ-3 ʹ�����޳��޳����� �Ա�������(peter panning)
int renderingShadow3CullFront(GLFWwindow* window);

// ������Ӱ-4 �޸�texture�߽����Ͳ���shader�������ж� �Ա����������over-sampling
int renderingShadow4FixOverSampling(GLFWwindow* window);

// ������Ӱ-final ʹ��PCF(percentage-closer filtering)
int renderingShadowsWithPCF(GLFWwindow* window);

