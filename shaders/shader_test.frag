#version 430 core
in vec3 normal;
void main()
{
	vec3 n=normalize(normal);
	gl_FragColor = vec4((n+1)/1.8, 1.0);
}
