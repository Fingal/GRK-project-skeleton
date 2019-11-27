#version 430 core
uniform vec3 lightSource;
in VS_OUT{
vec3 normal;
vec3 transformed_normal;
vec3 pos;
vec3 transformed_pos;
} vs_out;

vec3 WATER_COLOR = vec3(0.102, 0.5333, 0.9412);
vec3 GRASS_COLOR = vec3(0.2784, 0.7725, 0.1529);
vec3 ROCK_COLOR = vec3(0.302, 0.2941, 0.2745);
void main()
{
	float ambient=0.3;
	float diffuse=dot(normalize(vs_out.normal),normalize(lightSource-vs_out.transformed_pos));
	vec3 normal = normalize(vs_out.normal);
	float water = -clamp(vs_out.pos.y+2,-1.0,0.0);
	float rock = 1-pow(clamp(normal.y,0.0,0.7)/0.7,20);
	
	vec3 color = mix(GRASS_COLOR,ROCK_COLOR,rock);
	color = color*ambient+color*diffuse*0.7;

	color=mix(color,WATER_COLOR,water);

	gl_FragColor = vec4(color, 1.0);
}
