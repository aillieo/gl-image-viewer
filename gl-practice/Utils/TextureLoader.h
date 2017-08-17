#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GL/glew.h"


class TextureLoader
{
public:

    static unsigned char* loadTexture(char const *filename, int *x, int *y, int *comp, int req_comp);

    static void freeData(void* data);

	static unsigned int loadTexture(char const *filename);
    
	static unsigned int loadCubeMap(char const *filepath);

};

#endif
