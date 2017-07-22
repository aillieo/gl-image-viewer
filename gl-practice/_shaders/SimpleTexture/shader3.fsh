#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D uTexture;

void main()
{
	float gray;
    FragColor = texture(uTexture, TexCoord);
	if(gl_PointCoord.x > 1.0 && gl_PointCoord.y<1.0)
	{
		FragColor = FragColor * vec4(1.0,0,0,0);
	}
	else if(gl_PointCoord.x > 1.0 && gl_PointCoord.y>1.0)
	{
		FragColor = FragColor * vec4(0,1.0,0,0);
	}
	else if(gl_PointCoord.x < 1.0 && gl_PointCoord.y>1.0)
	{
		FragColor = FragColor * vec4(0,0,1.0,0);
	}
}