#version 330 core
#define NLIGHTS 1

in vec4 FragPos;

struct Light{
	vec3 ambient;
	vec3 specular;
	vec3 diffuse;

	vec3 position;
	vec3 direction;
	vec3 type;

	float constant;
	float linear;
	float quadratic;
	float exponent;
	float cosCutOff;
};

uniform Light u_light[NLIGHTS];
//uniform float far_plane;

void main()
{
    // get distance between fragment and light source
    float lightDistance = length(FragPos.xyz - u_light[0].position);
    
    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / 0.5;
    
    // Write this as modified depth
    gl_FragDepth = lightDistance;
}  