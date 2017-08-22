#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

layout (std140) uniform Mats
{
	mat4 model;
	mat4 view;
	mat4 projection;
};

out VS_OUT {
    vec3 normal;
} vs_out;



void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f); 
    mat3 normalMatrix = mat3(transpose(inverse(view * model)));
    vs_out.normal = vec3(projection * vec4(normalMatrix * aNormal, 1.0));
}
