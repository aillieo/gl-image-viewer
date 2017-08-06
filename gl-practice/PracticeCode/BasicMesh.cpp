#include "BasicMesh.h"

#ifdef WIN32
#include <windows.h>
#elif __APPLE__

#endif

#include "../Utils/Shader.h"

#include "../SceneManager.h"
#include "../Utils/TextureLoader.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


#include <sstream>
#include <iostream>


int basicMesh(GLFWwindow* window)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("", aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    
    return 0;
}
