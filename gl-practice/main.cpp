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
#include "PracticeCode/LightingMaps.h"
#include "PracticeCode/LightCasters.h"
#include "PracticeCode/MultipleLights.h"
#include "PracticeCode/LoadModel.h"
#include "PracticeCode/DepthTesting.h"
#include "PracticeCode/StencilTesting.h"
#include "PracticeCode/Blending.h"
#include "PracticeCode/FaceCulling.h"
#include "PracticeCode/FrameBuffers.h"
#include "PracticeCode/CubeMaps.h"
#include "PracticeCode/AdvancedGLSL.h"
#include "PracticeCode/UseGeometryShader.h"
#include "PracticeCode/Instancing.h"
#include "PracticeCode/AntiAliasing.h"
#include "PracticeCode/AdvancedLighting.h"
#include "PracticeCode/ShadowMapping.h"
#include "PracticeCode/PointShadows.h"
#include "PracticeCode/NormalMapping.h"
#include "PracticeCode/ParallaxMapping.h"
#include "PracticeCode/HighDynamicRange.h"


int main()  
{  

	GLFWwindow* window = createWindow();
	if(nullptr == window)
	{
		return -1;
	}

	//
	SceneManager::sceneIndexMax = 95;
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
        case 31:
			// 青色塑料盒子
			cyanPlasticBox(window);
			break;
        case 32:
			// 金箱子
			goldenBox(window);
			break;
        case 33:
			// 银箱子
			silverBox(window);
			break;
        case 34:
			// 橡胶箱子
			rubberBox(window);
			break;
        case 35:
			// 漫反射贴图
			diffuseMap(window);
			break;
        case 36:
			// 镜面反射贴图
			specularMap(window);
			break;
        case 37:
			// 发光贴图
			emissionMap(window);
			break;
		case 38:
			// 平行光
			directionalLight(window);
			break;
		case 39:
			// 点光源
			pointLight(window);
			break;
		case 40:
			// 聚光灯
			spotlight(window);
			break;
		case 41:
            // 多个光源
            multipleLights(window);
            break;
        case 42:
            // 三个点光源 红绿蓝
            multipleLightsRGB(window);
            break;
        case 43:
            // 加载模型
            loadModel(window);
			break;
		case 44:
			// 深度检测函数GL_ALWAYS
			depthFuncAlways(window);
			break;
		case 45:
			// 深度可视化
			visualizingDepth(window);
			break;
		case 46:
			// 深度可视化（线性）
			visualizingDepthLinear(window);
			break;
		case 47:
			// 场景只显示指定区域
			simpleClip(window);
			break;
		case 48:
			// 给箱子加轮廓
			boxOutlining(window);
			break;
		case 49:
			// 片段着色器中丢弃透明片段
			discardFragAlpha(window);
			break;
		case 50:
			// 按顺序绘制透明物体
			transparentWithSorting(window);
			break;
		case 51:
			// 使用面剔除
			useFaceCulling( window);
			break;
		case 52:
			// 渲染到纹理
			RenderToTexture(window);
			break;
		case 53:
			// 四种后处理
			postProcessings(window);
			break;
		case 54:
			// 错误的天空盒（不控制model位移）
			badSkyBox(window);
			break;
		case 55:
			// 正确的天空盒
			rightSkyBox(window);
			break;
		case 56:
			// 立方体反射
			boxReflection(window);
			break;
		case 57:
			// 模型反射
			modelReflection(window);
			break;
		case 58:
			// 立方体折射
			boxRefraction(window);
			break;
		case 59:
			// 模型折射
			modelRefraction(window);
			break;
		case 60:
			// 使用gl_PointSize
			usePointSize(window);
			break;
		case 61:
			// 使用gl_FragCoord
			useFragCoord(window);
			break;
		case 62:
			// 使用gl_FrontFacing
			useFrontFacing(window);
			break;
		case 63:
			// 使用UBO uniform buffer object
			useUBO(window);
			break;
        case 64:
            // 在几何着色器中把点变成线
            gshPointToLine(window);
            break;
        case 65:
            // 在几何着色器中把点变成“房子”
            gshPointToHouse(window);
            break;
        case 66:
            // 在几何着色器中把点变成不同颜色的“房子”
            gshPointToHouseColor(window);
            break;
        case 67:
            // 在几何着色器中把点变成带白色顶部的不同颜色的“房子”
            gshPointToHouseColorWithWhite(window);
            break;
        case 68:
            // 使用着色器制造爆炸效果
            gshExplode(window);
            break;
        case 69:
            // 使用着色器显示法线
            gshDisplayNormals(window);
            break;
		case 70:
			// 阵列 不使用Instancing
			arrayWithoutInstancing(window);
			break;
		case 71:
			// 阵列 使用Instancing
			arrayWithInstancing(window);
			break;
		case 72:
			// 阵列 使用Instancing 尺寸渐变
			arrayWithInstancingScaling(window);
			break;
		case 73:
			// 行星带 不使用Instancing
			asteroidFieldWithoutInstancing(window);
			break;
		case 74:
			// 行星带 使用Instancing
			asteroidFieldWithInstancing(window);
			break;
		case 75:
			// 不使用抗锯齿
			cubeWithoutAA(window);
			break;
		case 76:
			// 使用多重采样抗锯齿
			cubeWithMSAA(window);
			break;
		case 77:
			// 使用离屏多重采样抗锯齿 绘制到frameBuffer再blit到屏幕
			cubeWithOffScreenMSAA(window);
			break;
		case 78:
			// 使用离屏多重采样抗锯齿 通过帧缓冲纹理
			cubeWithOffScreenMSAATexture(window);
			break;
		case 79:
			// 使用自定义抗锯齿算法
			cubeCustomAAAlgorithm(window);
			break;
        case 80:
            // 点光源照地板 使用Phong
            floorPhong(window);
            break;
        case 81:
            // 点光源照地板 使用Blinn-Phong
            floorBlinnPhong(window);
            break;
        case 82:
            // 用于绘制阴影的深度可视化
            depthMapForShadow(window);
            break;
        case 83:
            // 绘制阴影-1 初步实现
            renderingShadow1Raw(window);
            break;
        case 84:
            // 绘制阴影-2 使用偏移减少阴影失真
            renderingShadow2Bias(window);
            break;
        case 85:
            // 绘制阴影-3 使用面剔除剔除正面 以避免悬浮(peter panning)
            renderingShadow3CullFront(window);
            break;
        case 86:
            // 绘制阴影-4 修改texture边界类型并在shader中增加判断 以避免采样过多over-sampling
            renderingShadow4FixOverSampling(window);
            break;
        case 87:
            // 绘制阴影-final 使用PCF(percentage-closer filtering)
            renderingShadowsWithPCF(window);
			break;
		case 88:
			// 绘制点光源的阴影
			renderPointShadow(window);
			break;
		case 89:
			// 展示点光源阴影的深度贴图
			renderPointShadowShowDepth(window);
			break;
		case 90:
			// 绘制点光源阴影并使用PCF
			renderPointShadowPCF(window);
			break;
		case 91:
			// 法线贴图 将TBN传给片段着色器
			normalMappingTBN1(window);
			break;
		case 92:
			// 法线贴图 在片段着色器中使用切线空间计算光照
			normalMappingTBN2(window);
			break;
		case 93:
			// 视差贴图
			parallaxMapping(window);
			break;
		case 94:
			// 视差贴图 陡峭视差映射
			parallaxMappingSteep(window);
			break;
		case 95:
			// 视差贴图 视差遮蔽映射
			parallaxMappingOcclusion(window);
			break;
        case 96:
            // 视差贴图 视差遮蔽映射
            HDRWithHighExposure(window);
            break;
        case 97:
            // 视差贴图 视差遮蔽映射
            HDRWithLowExposure(window);
            break;


                




            


		default:
			break;
		}
	}

	glfwTerminate();

	return 0;

}


