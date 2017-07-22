#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D uTexture;

void main()
{
	float gray;
    FragColor = texture(uTexture, TexCoord);
	gray = 0.3 * FragColor.r + 0.59 * FragColor.g + 0.11 * FragColor.b;
	FragColor.r = gray;
	FragColor.g = gray;
	FragColor.b = gray;
}