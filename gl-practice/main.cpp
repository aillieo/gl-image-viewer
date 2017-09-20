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
			// ����һ��������
			drawHelloTriangleVAO(window);
			break;
		case 1:
			// �������������� ��ʹ��EBO
			drawTwoTriangleNoEBO(window);
			break;
		case 2:
			// �������������� ��ʹ��EBO
			drawTwoTriangleEBO(window);
			break;
		case 3:
			// �������������� �ֱ�ʹ������VAO
			drawTwoTriangleTwoVAO(window);
			break;
		case 4:
			// �������������� ʹ�ò�ͬ��shader ʹ����ɫ��ͬ
			drawHelloTriangleTwoShader(window);
			break;
		case 5:
			// �������������� ʹ�ò�ͬ��shader ʹ����ɫ��ͬ ��ʹ��EBO
			drawHelloTriangleTwoShaderEBO(window);
			break;
		case 6:
			// ʹ��Shader��
			useShaderClass(window);
			break;
		case 7:
			// vsh�����ɫ
			colorFromVSH(window);
			break;
		case 8:
			// ��ɫ
			changeColorByUniform(window);
			break;
		case 9:
			// ��λ��
			changePosByUniform(window);
			break;
		case 10:
			// ��VBOд����ɫ
			triangleColorVBO(window);
			break;
		case 11:
			// �������μ�������
			textureForTriangle(window);
			break;
		case 12:
			// ��ʾͼƬ
			displayImage(window);
			break;
		case 13:
			// gray
			grayImage(window);
			break;
		case 14:
			// ����ɫ���ĸ�ͼƬ
			fourImages(window);
			break;
		case 15:
			// ����������
			twoTextureMix(window);
			break;
		case 16:
			// ���ֲ�ͬ������ʽ�Ŵ�
			magnifyTextures(window);
			break;
		case 17:
			// ƽ������ת
			rotate2D(window);
			break;
		case 18:
			// ƽ��������ת
			moveScaleRotate(window);
			break;
		case 19:
			// ƽ��������ת
			box3D(window);
			break;
		case 20:
            // ����ռ���ת
            rotate3DMulti(window);
            break;
		case 21:
			// ��view������ת�����
			cameraRotateView(window);
			break;
		case 22:
			// ��lookat��ת�����
			cameraRotateLookAt(window);
			break;
		case 23:
			// ASDW���������
			cameraControl(window);
			break;
		case 24:
			// ����ɫ������������Դ û��ʹ�ù���
			noLighting(window);
			break;
		case 25:
			// ֻ�л�����
			ambientAlone(window);
			break;
		case 26:
			// ֻ��������
			diffuseAlone(window);
			break;
		case 27:
			// ֻ�о��淴��
			specularAlone(window);
			break;
		case 28:
			// ʹ��Phong����ģ��
			PhongLighting(window);
			break;
		case 29:
			// ʹ��Phong����ģ�� �˶��Ĺ�Դ
			PhongLightingMoving(window);
			break;
        case 30:
            // ʹ�ò���
            useMaterials(window);
            break;
        case 31:
			// ��ɫ���Ϻ���
			cyanPlasticBox(window);
			break;
        case 32:
			// ������
			goldenBox(window);
			break;
        case 33:
			// ������
			silverBox(window);
			break;
        case 34:
			// ������
			rubberBox(window);
			break;
        case 35:
			// ��������ͼ
			diffuseMap(window);
			break;
        case 36:
			// ���淴����ͼ
			specularMap(window);
			break;
        case 37:
			// ������ͼ
			emissionMap(window);
			break;
		case 38:
			// ƽ�й�
			directionalLight(window);
			break;
		case 39:
			// ���Դ
			pointLight(window);
			break;
		case 40:
			// �۹��
			spotlight(window);
			break;
		case 41:
            // �����Դ
            multipleLights(window);
            break;
        case 42:
            // �������Դ ������
            multipleLightsRGB(window);
            break;
        case 43:
            // ����ģ��
            loadModel(window);
			break;
		case 44:
			// ��ȼ�⺯��GL_ALWAYS
			depthFuncAlways(window);
			break;
		case 45:
			// ��ȿ��ӻ�
			visualizingDepth(window);
			break;
		case 46:
			// ��ȿ��ӻ������ԣ�
			visualizingDepthLinear(window);
			break;
		case 47:
			// ����ֻ��ʾָ������
			simpleClip(window);
			break;
		case 48:
			// �����Ӽ�����
			boxOutlining(window);
			break;
		case 49:
			// Ƭ����ɫ���ж���͸��Ƭ��
			discardFragAlpha(window);
			break;
		case 50:
			// ��˳�����͸������
			transparentWithSorting(window);
			break;
		case 51:
			// ʹ�����޳�
			useFaceCulling( window);
			break;
		case 52:
			// ��Ⱦ������
			RenderToTexture(window);
			break;
		case 53:
			// ���ֺ���
			postProcessings(window);
			break;
		case 54:
			// �������պУ�������modelλ�ƣ�
			badSkyBox(window);
			break;
		case 55:
			// ��ȷ����պ�
			rightSkyBox(window);
			break;
		case 56:
			// �����巴��
			boxReflection(window);
			break;
		case 57:
			// ģ�ͷ���
			modelReflection(window);
			break;
		case 58:
			// ����������
			boxRefraction(window);
			break;
		case 59:
			// ģ������
			modelRefraction(window);
			break;
		case 60:
			// ʹ��gl_PointSize
			usePointSize(window);
			break;
		case 61:
			// ʹ��gl_FragCoord
			useFragCoord(window);
			break;
		case 62:
			// ʹ��gl_FrontFacing
			useFrontFacing(window);
			break;
		case 63:
			// ʹ��UBO uniform buffer object
			useUBO(window);
			break;
        case 64:
            // �ڼ�����ɫ���аѵ�����
            gshPointToLine(window);
            break;
        case 65:
            // �ڼ�����ɫ���аѵ��ɡ����ӡ�
            gshPointToHouse(window);
            break;
        case 66:
            // �ڼ�����ɫ���аѵ��ɲ�ͬ��ɫ�ġ����ӡ�
            gshPointToHouseColor(window);
            break;
        case 67:
            // �ڼ�����ɫ���аѵ��ɴ���ɫ�����Ĳ�ͬ��ɫ�ġ����ӡ�
            gshPointToHouseColorWithWhite(window);
            break;
        case 68:
            // ʹ����ɫ�����챬ըЧ��
            gshExplode(window);
            break;
        case 69:
            // ʹ����ɫ����ʾ����
            gshDisplayNormals(window);
            break;
		case 70:
			// ���� ��ʹ��Instancing
			arrayWithoutInstancing(window);
			break;
		case 71:
			// ���� ʹ��Instancing
			arrayWithInstancing(window);
			break;
		case 72:
			// ���� ʹ��Instancing �ߴ罥��
			arrayWithInstancingScaling(window);
			break;
		case 73:
			// ���Ǵ� ��ʹ��Instancing
			asteroidFieldWithoutInstancing(window);
			break;
		case 74:
			// ���Ǵ� ʹ��Instancing
			asteroidFieldWithInstancing(window);
			break;
		case 75:
			// ��ʹ�ÿ����
			cubeWithoutAA(window);
			break;
		case 76:
			// ʹ�ö��ز��������
			cubeWithMSAA(window);
			break;
		case 77:
			// ʹ���������ز�������� ���Ƶ�frameBuffer��blit����Ļ
			cubeWithOffScreenMSAA(window);
			break;
		case 78:
			// ʹ���������ز�������� ͨ��֡��������
			cubeWithOffScreenMSAATexture(window);
			break;
		case 79:
			// ʹ���Զ��忹����㷨
			cubeCustomAAAlgorithm(window);
			break;
        case 80:
            // ���Դ�յذ� ʹ��Phong
            floorPhong(window);
            break;
        case 81:
            // ���Դ�յذ� ʹ��Blinn-Phong
            floorBlinnPhong(window);
            break;
        case 82:
            // ���ڻ�����Ӱ����ȿ��ӻ�
            depthMapForShadow(window);
            break;
        case 83:
            // ������Ӱ-1 ����ʵ��
            renderingShadow1Raw(window);
            break;
        case 84:
            // ������Ӱ-2 ʹ��ƫ�Ƽ�����Ӱʧ��
            renderingShadow2Bias(window);
            break;
        case 85:
            // ������Ӱ-3 ʹ�����޳��޳����� �Ա�������(peter panning)
            renderingShadow3CullFront(window);
            break;
        case 86:
            // ������Ӱ-4 �޸�texture�߽����Ͳ���shader�������ж� �Ա����������over-sampling
            renderingShadow4FixOverSampling(window);
            break;
        case 87:
            // ������Ӱ-final ʹ��PCF(percentage-closer filtering)
            renderingShadowsWithPCF(window);
			break;
		case 88:
			// ���Ƶ��Դ����Ӱ
			renderPointShadow(window);
			break;
		case 89:
			// չʾ���Դ��Ӱ�������ͼ
			renderPointShadowShowDepth(window);
			break;
		case 90:
			// ���Ƶ��Դ��Ӱ��ʹ��PCF
			renderPointShadowPCF(window);
			break;
		case 91:
			// ������ͼ ��TBN����Ƭ����ɫ��
			normalMappingTBN1(window);
			break;
		case 92:
			// ������ͼ ��Ƭ����ɫ����ʹ�����߿ռ�������
			normalMappingTBN2(window);
			break;
		case 93:
			// �Ӳ���ͼ
			parallaxMapping(window);
			break;
		case 94:
			// �Ӳ���ͼ �����Ӳ�ӳ��
			parallaxMappingSteep(window);
			break;
		case 95:
			// �Ӳ���ͼ �Ӳ��ڱ�ӳ��
			parallaxMappingOcclusion(window);
			break;
        case 96:
            // �Ӳ���ͼ �Ӳ��ڱ�ӳ��
            HDRWithHighExposure(window);
            break;
        case 97:
            // �Ӳ���ͼ �Ӳ��ڱ�ӳ��
            HDRWithLowExposure(window);
            break;


                




            


		default:
			break;
		}
	}

	glfwTerminate();

	return 0;

}


