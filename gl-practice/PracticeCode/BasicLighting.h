#pragma once

#include "../Utils/GLMethod.h"

// ����ɫ������������Դ û��ʹ�ù���
int noLighting(GLFWwindow* window);

// ֻ�л�����
int ambientAlone(GLFWwindow* window);

// ֻ��������
int diffuseAlone(GLFWwindow* window);

// ֻ�о��淴��
int specularAlone(GLFWwindow* window);

// ʹ��Phong����ģ��
int PhongLighting(GLFWwindow* window);

