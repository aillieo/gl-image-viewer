#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform float timeFactor;

void main()
{
    FragColor = mix(texture(uTexture0, TexCoord), texture(uTexture1, TexCoord), timeFactor);
}