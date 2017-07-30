#include "Utils/GLMethod.h"
#include "SceneManager.h"

#include "PracticeCode/HelloTriangle.h"
#include "PracticeCode/SimpleShader.h"
#include "PracticeCode/SimpleTexture.h"
#include "PracticeCode/SimpleTransform.h"
#include "PracticeCode/SimpleTransform3D.h"
#include "PracticeCode/SimpleCamera.h"
#include "PracticeCode/BasicLighting.h"
#include "PracticeCode/BasicMaterials.h"



int main()  
{  

	GLFWwindow* window = createWindow();
	if(nullptr == window)
	{
		return -1;
	}

	//
	SceneManager::sceneIndexMax = 30;
	SceneManager::index = SceneManager::sceneIndexMax;

	while (!glfwWindowShouldClose(window))
	{

		SceneManager::willChangeScene = false;

		switch (SceneManager::index)
		{
		case 0:
			// 绘制一个三角形
			drawHelloTriangleVAO(window);
			break;
		case 1:
			// 绘制两个三角形 不使用EBO
			drawTwoTriangleNoEBO(window);
			break;
		case 2:
			// 绘制两个三角形 并使用EBO
			drawTwoTriangleEBO(window);
			break;
		case 3:
			// 绘制两个三角形 分别使用两个VAO
			drawTwoTriangleTwoVAO(window);
			break;
		case 4:
			// 绘制两个三角形 使用不同的shader 使其颜色不同
			drawHelloTriangleTwoShader(window);
			break;
		case 5:
			// 绘制两个三角形 使用不同的shader 使其颜色不同 并使用EBO
			drawHelloTriangleTwoShaderEBO(window);
			break;
		case 6:
			// 使用Shader类
			useShaderClass(window);
			break;
		case 7:
			// vsh输出颜色
			colorFromVSH(window);
			break;
		case 8:
			// 变色
			changeColorByUniform(window);
			break;
		case 9:
			// 变位置
			changePosByUniform(window);
			break;
		case 10:
			// 向VBO写入颜色
			triangleColorVBO(window);
			break;
		case 11:
			// 给三角形加上纹理
			textureForTriangle(window);
			break;
		case 12:
			// 显示图片
			displayImage(window);
			break;
		case 13:
			// gray
			grayImage(window);
			break;
		case 14:
			// 带颜色的四个图片
			fourImages(window);
			break;
		case 15:
			// 两张纹理混合
			twoTextureMix(window);
			break;
		case 16:
			// 两种不同采样方式放大
			magnifyTextures(window);
			break;
		case 17:
			// 平面内旋转
			rotate2D(window);
			break;
		case 18:
			// 平移缩放旋转
			moveScaleRotate(window);
			break;
		case 19:
			// 平移缩放旋转
			box3D(window);
			break;
		case 20:
            // 多个空间旋转
            rotate3DMulti(window);
            break;
		case 21:
			// 用view矩阵旋转摄像机
			cameraRotateView(window);
			break;
		case 22:
			// 用lookat旋转摄像机
			cameraRotateLookAt(window);
			break;
		case 23:
			// ASDW控制摄像机
			cameraControl(window);
			break;
		case 24:
			// 带颜色的物体和虚拟光源 没有使用光照
			noLighting(window);
			break;
		case 25:
			// 只有环境光
			ambientAlone(window);
			break;
		case 26:
			// 只有漫反射
			diffuseAlone(window);
			break;
		case 27:
			// 只有镜面反射
			specularAlone(window);
			break;
		case 28:
			// 使用Phong光照模型
			PhongLighting(window);
			break;
		case 29:
			// 使用Phong光照模型 运动的光源
			PhongLightingMoving(window);
			break;
        case 30:
            // 使用材质
            useMaterials(window);
            break;
		default:
			break;
		}
	}

	glfwTerminate();

	return 0;

}


