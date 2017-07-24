#ifndef SHADER_H
#define SHADER_H


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GL/glew.h"


class Shader
{
public:

	unsigned int ID;


    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);


    void use();


    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, GLsizei count, GLboolean transpose, const GLfloat* value) const;
    void setMat4(const std::string &name, const GLfloat* value) const;

private:
	
	void checkCompileErrors(unsigned int shader, std::string type);

};

#endif
