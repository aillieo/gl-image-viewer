#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2DMS screenTextureMS;

void main()
{
	ivec2 texSize = textureSize(screenTextureMS);
	vec4 colorSample = texelFetch(screenTextureMS, ivec2(TexCoords* texSize), 3);  // 4th subsample
    vec3 col = colorSample.rgb;
    FragColor = vec4(col, 1.0);
} 
