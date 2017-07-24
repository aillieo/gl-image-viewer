#include "Utils/GLMethod.h"
#include "SceneManager.h"

#include "PracticeCode/HelloTriangle.h"
#include "PracticeCode/SimpleShader.h"
#include "PracticeCode/SimpleTexture.h"
#include "PracticeCode/SimpleTransform.h"


int main()  
{  

	GLFWwindow* window = createWindow();
	if(nullptr == window)
	{
		return -1;
	}

	//
	SceneManager::sceneIndexMax = 17;


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
		default:
			break;
		}
		
	}
	

	glfwTerminate();

	return 0;

}


