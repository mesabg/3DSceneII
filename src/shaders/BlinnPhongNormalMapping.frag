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
uniform sampler2D u_normal_texture;

//-- Out Value
out vec4 resultingColor;


float CalculateAttenuation(in vec3 N, in vec3 L, in Light light, in float dist){
    float NdotL = max(dot(N,L), 0.0);

    //-- Directional
    float directional = 1.0;

    //-- Point Light
    float point_light = 0.0;
    if ( NdotL > 0.0 )
        point_light = 1.0 / (light.constant + light.linear*dist + light.quadratic*dist*dist);

    //-- Spot Light
    float spot_effect = dot(normalize(light.direction), normalize(-L));
    float spot_light = 0.0;
    if ( NdotL > 0.0 )
        if (spot_effect > light.cosCutOff){
            spot_effect = pow(spot_effect, light.exponent);
            spot_light = spot_effect / (light.constant + light.linear*dist + light.quadratic*dist*dist);
        }

	return light.type.x*directional + light.type.y*point_light + light.type.y*spot_light;
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
      specularTerm = max(pow(dot(N, H), u_material.shininess),0.0);
   }

   return specularTerm * u_material.specular * u_light[0].specular;
}


vec4 calculateBlinnPhong(in vec3 N, in vec3 L, in vec3 V) {
   float NdotL = max(dot(N,L), 0.0);
   float attenuation = CalculateAttenuation(N, L, u_light[0], dist);
   vec3 BlinnPhongColor = vec3(0.0);

   //-- get Blinn-Phong reflectance components
   vec3 Iamb = ambientLighting();
   vec3 Idif = diffuseLighting(N, L);
   vec3 Ispe = specularLightingBlinn(N, L, V);

   //-- combination of all components and diffuse color of the object
   if (NdotL > 0.0)
    BlinnPhongColor = Iamb + attenuation*Idif + attenuation*Ispe;

   //-- Calculate Attenuation Depending on the light type
   return vec4(BlinnPhongColor, 1.0);
} 




void main(void){
    //-- Prev Calculations (All Values are in tangent space)
    vec3 L = normalize(o_toLight); 
    vec3 N = normalize( (2.0 * texture(u_normal_texture, o_textureCoord, -1.0) - 1.0).xyz );
    vec3 V = normalize(o_toCamera);

	vec4 BlinnPhong = calculateBlinnPhong(N, L, V);
	resultingColor = mix(BlinnPhong, texture(u_texture, o_textureCoord), 0.7);
}