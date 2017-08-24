#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

uniform vec2 offset;
out vec3 fColor;

void main()
{
   gl_Position = vec4(aPos + offset, 0.0, 1.0);
   fColor = aColor;
}