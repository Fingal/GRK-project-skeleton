#version 430 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;

out VS_OUT{
vec3 normal;
vec3 transformed_normal;
vec3 pos;
vec3 transformed_pos;
} vs_out;

void main()
{
	//normal=(modelMatrix*vec4(vertexNormal,0)).xyz;
	vs_out.normal = vertexNormal;
	vs_out.pos = vertexPosition;
	vs_out.transformed_normal = (modelMatrix * vec4(vertexNormal, 0.0)).xyz;
	vs_out.transformed_pos = (modelMatrix * vec4(vertexPosition, 1.0)).xyz;
	gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
}
