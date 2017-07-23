#include "TextureLoader.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


unsigned char* TextureLoader::loadTexture(char const *filename, int *x, int *y, int *comp, int req_comp)
{
    
    const char* texturePath = "../../gl-practice/_textures/";
    
    std::stringstream tPath;
    tPath<<texturePath<<filename;
    
    // open files
    
    return stbi_load(tPath.str().c_str(), x, y, comp, req_comp);
    
}

void TextureLoader::freeData(void* data)
{
    return stbi_image_free(data);
}
