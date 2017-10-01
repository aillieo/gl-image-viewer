#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;
uniform int channels;

void main()
{             
	if(channels == 4)
	{
		FragColor = texture(scene, TexCoords); 
	}
	else if(channels == 3)
	{
    	vec3 color = texture(scene, TexCoords).rgb;
	    FragColor = vec4(color, 1.0);
	}
	else if(channels == 1)
	{
	    float color = texture(scene, TexCoords).a;
    	FragColor = vec4(color);
	}


}