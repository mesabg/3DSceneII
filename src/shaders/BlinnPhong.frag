#version 330
#define NLIGHTS 1

//-- In values
in vec3 o_normal;
in vec3 o_toLight;
in vec3 o_toCamera;
in vec2 o_textureCoord;
in float dist;

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
uniform sampler2D u_texture;


float attenuation = 1.0;

//-- Out Value
out vec4 resultingColor;


float CalculateAttenuation(){
	return 1.0;
}


// -- returns intensity of reflected ambient lighting
vec3 ambientLighting(){
	return u_material.ambient * u_light[0].ambient;
}


// -- returns intensity of diffuse reflection
vec3 diffuseLighting(in vec3 N, in vec3 L){
   return max(dot(N, L), 0.0) * u_material.diffuse * u_light[0].diffuse;
}


// -- returns intensity of specular reflection
vec3 specularLightingBlinn(in vec3 N, in vec3 L, in vec3 V){
   float specularTerm = 0;

   if(dot(N, L) > 0){
      // -- half vector
      vec3 H = normalize(L + V);
      specularTerm = CalculateAttenuation() * max(pow(dot(N, H), u_material.shininess),0.0);
   }

   return specularTerm * u_material.specular * u_light[0].specular;
}


vec4 calculateBlinnPhong(void) {
   //-- normalize vectors after interpolation
   vec3 L = normalize(o_toLight); 
   vec3 N = normalize(o_normal);
   vec3 V = normalize(o_toCamera);
   vec3 R = normalize(reflect(L, N));
   vec4 BlinnPhongColor;

   //-- get Blinn-Phong reflectance components
   vec3 Iamb = ambientLighting();
   vec3 Idif = diffuseLighting(N, L);
   vec3 Ispe = specularLightingBlinn(N, L, V);

   //-- combination of all components and diffuse color of the object
   BlinnPhongColor.xyz = Iamb + Idif + Ispe;
   BlinnPhongColor.a = 1.0;
   return BlinnPhongColor;
} 




void main(void){
	vec4 BlinnPhong = calculateBlinnPhong();
	resultingColor = mix(BlinnPhong, texture(u_texture, o_textureCoord), 0.5);
}