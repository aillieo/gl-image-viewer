#version 330 core
layout (location = 0)
in vec3 aPos;

uniform float timeFactor; // 在OpenGL程序代码中设定这个变量

void main()
{
    gl_Position = vec4(aPos.x * 0.5 * (timeFactor + 2.0), aPos.y + 0.5*timeFactor, aPos.z, 1.0);
}