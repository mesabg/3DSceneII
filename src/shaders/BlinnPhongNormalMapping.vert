#version 330
#define NLIGHTS 1

in layout(location=0) vec3 i_position;
in layout(location=1) vec2 i_texture;
in layout(location=2) vec3 i_normal;
in layout(location=3) vec3 i_tangent;

out vec3 o_normal;
out vec3 o_toLight;
out vec3 o_toCamera;
out vec2 o_textureCoord;
out float dist;

//-- parameters of the light
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

//-- parameters of the material
struct Material{
	vec3 ambient;
	vec3 specular;
	vec3 diffuse;

	float shininess;
	float roughness;
	float fresnel;
	float albedo;
};

uniform Light u_light[NLIGHTS];
uniform Material u_material;
uniform vec3 u_camera_position;
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;
uniform mat4 u_normal_matrix;
uniform mat4 u_model_matrix;
uniform vec4 u_shadingBitMap;
uniform int u_textureIsActive;

void main(void){
	vec4 worldPosition = u_model_matrix * vec4(i_position, 1.0);

	//-- normal in world space
	o_normal =  vec3( normalize(  u_model_matrix * vec4(i_normal, 0.0)) );

    //-- Normal Mapping Calculations
    vec3 normal = o_normal;
    vec3 tangent = normalize((u_model_matrix * vec4(i_tangent, 0.0)).xyz);
    vec3 bitangent = normalize(cross(normal, tangent));
    mat3 TBN = mat3(
        tangent.x, bitangent.x, normal.x,
        tangent.y, bitangent.y, normal.y,
        tangent.z, bitangent.z, normal.z
    );

	//-- direction to light
	vec3 VP;
	VP = u_light[0].position  - worldPosition.xyz;
	o_toLight = normalize(VP);
    o_toLight = TBN * o_toLight; 
	dist = length(VP);

	//-- direction to camera
	o_toCamera = normalize( u_camera_position - worldPosition.xyz );
    o_toCamera = TBN * o_toCamera;

	//-- screen space coordinates of the vertex
	o_textureCoord = i_texture;
	gl_Position = u_projection_matrix * u_view_matrix * worldPosition;
} 
