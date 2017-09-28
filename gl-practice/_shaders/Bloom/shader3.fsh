#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D hdrBuffer;
uniform bool bloom;

void main()
{             
    const float gamma = 2.2;
    const float threshold = 1.0f;
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;
    if(hdrColor.r < threshold && hdrColor.g < threshold && hdrColor.b < threshold)
        hdrColor = vec3(0.0f);
    vec3 result = hdrColor;
    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
}