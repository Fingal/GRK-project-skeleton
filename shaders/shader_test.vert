#version 430 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;
out vec3 normal;
void main()
{
	//normal=(modelMatrix*vec4(vertexNormal,0)).xyz;
	normal=vertexNormal;
	gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
}
