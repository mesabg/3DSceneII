#version 330
#define NLIGHTS 1

//-- Parameters of the light (Struct)
struct Light{
	vec3 ambient;
	vec3 specular;
	vec3 diffuse;

	vec3 position;
    vec3 position_tangent;
	vec3 direction;
    vec3 direction_tangent;
    float dist;
	vec3 type;
};

//-- Attenuation parameters (struct)
struct Attenuation{
    //-- To point light / spot light calculations
	float constant;
	float linear;
	float quadratic;

    //-- To spot light calculations
    vec3 direction;
	float exponent;
	float inner_cosine;
    float outer_cosine;
};

//-- Parameters of the material (Struct)
struct Material{
	vec3 ambient;
	vec3 specular;
	vec3 diffuse;

	float shininess;
	float roughness;
	float fresnel;
	float albedo;
};

//-- In values
in layout(location=0) vec3 i_position;
in layout(location=1) vec2 i_texture;
in layout(location=2) vec3 i_normal;
in layout(location=3) vec3 i_tangent;

//-- Out Values (After some calculations)
out vec3 o_position;
out vec3 o_position_tangent;
out vec3 o_normal;
out vec3 o_view;
out vec3 o_view_tangent;
out Light o_light[NLIGHTS];
out vec2 o_texture_coord;
out vec4 o_shadow_coord;
out vec3 reflectedVector;
out vec3 refractedVector;
out mat3 TBN;

//-- Constant in variables
uniform Light u_light[NLIGHTS];
uniform Attenuation u_attenuation[NLIGHTS];
uniform Material u_material;
uniform vec3 u_camera_position;
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;
uniform mat4 u_model_matrix;
uniform mat4 u_depth_biasMVP; 
uniform int u_texture_state;
uniform float u_refracted_index;
uniform int u_parallax_mapped;
uniform float u_parallax_factor;

void main(void){
	vec4 worldPosition = u_model_matrix * vec4(i_position, 1.0);

	//-- Normal Calculations
	o_normal =  vec3( normalize(  u_model_matrix * vec4(i_normal, 0.0)) );

    //-- Normal Mapping Calculations
    vec3 normal = o_normal;
    vec3 tangent = normalize((u_model_matrix * vec4(i_tangent, 0.0)).xyz);
    vec3 bitangent = normalize(cross(normal, tangent));
	TBN = transpose(mat3(tangent, bitangent, normal));

    //-- Position in tangent space
	o_position = worldPosition.xyz;
    o_position_tangent = TBN * worldPosition.xyz;

	//-- Light calculations - Direction to light (for each light)
	vec3 VP;
    for (int i=0; i<NLIGHTS; i++){
        VP = u_light[i].position  - worldPosition.xyz;
        o_light[i] = u_light[i];
        o_light[i].direction = normalize(VP);
        o_light[i].direction_tangent = TBN * o_light[i].direction; 
        o_light[i].position_tangent = TBN * o_light[i].position; 
        o_light[i].dist = length(VP);
    }

	//-- Camera Calculations
	o_view = normalize( u_camera_position - worldPosition.xyz );
    o_view_tangent = TBN * o_view;

	//-- Texture Coords
	o_texture_coord = i_texture;
    o_shadow_coord = u_depth_biasMVP * worldPosition;

	//-- Calculate reflected vector
	vec3 viewVector = normalize(worldPosition.xyz - u_camera_position);
	reflectedVector = reflect(viewVector, normalize(o_normal));
	refractedVector = refract(viewVector, normalize(o_normal), u_refracted_index);

    //-- Final vertex position
	gl_Position = u_projection_matrix * u_view_matrix * worldPosition;
} 