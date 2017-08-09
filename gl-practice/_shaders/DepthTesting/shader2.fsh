#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{             
    FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}  
