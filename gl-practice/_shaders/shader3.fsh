#version 330 core
in vec4 vColor;
out vec4 FragColor;

uniform float red; // 在OpenGL程序代码中设定这个变量
uniform float blue; // 在OpenGL程序代码中设定这个变量

void main()
{
   FragColor = vec4(red,0.0f,blue,1.0);
}