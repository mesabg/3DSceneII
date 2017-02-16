#version 330

//-- In values
in vec3 o_normal;
in vec3 o_toLight;
in vec3 o_toCamera;
in vec2 o_textureCoord;

in vec3 diffuse, ambient;
in float dist;

uniform vec3 u_lightPosition;

//-- parameters of the light
uniform vec3 u_lightAmbientIntensitys; 
uniform vec3 u_lightDiffuseIntensitys; 
uniform vec3 u_lightSpecularIntensitys;
uniform vec3 u_lightAttenuation;

//-- parameters of the material
uniform vec3 u_matAmbientReflectances; 
uniform vec3 u_matDiffuseReflectances; 
uniform vec3 u_matSpecularReflectances; 

//-- Variables
uniform vec3 u_lightSpotDirection;
uniform float u_lightSpotExp;
uniform float u_spotCosCutOff;
uniform float u_shininess; 
uniform float u_roughness;
uniform float u_fresnel;
uniform float u_albedo;
uniform vec4 u_shadingBitMap;
uniform int u_textureIsActive;
uniform vec3 u_lightType;
uniform sampler2D u_texture;

float attenuation = 1.0;

//-- Out Value
out vec4 resultingColor;


float CalculateAttenuation(){
	if (u_lightType.x == 1 ){
		//-- Direcional
		return 1.0;
	}else if (u_lightType.y == 1){
		//-- Puntual
		return 1.0 / (u_lightAttenuation.x + u_lightAttenuation.y * dist + u_lightAttenuation.z * dist * dist);
	}else if (u_lightType.z == 1){
		//-- Reflector
		float spotEffect;
		spotEffect = dot(normalize(u_lightSpotDirection), normalize(o_toLight));

		if ( spotEffect > u_spotCosCutOff )
			return spotEffect / (u_lightAttenuation.x + u_lightAttenuation.y * dist + u_lightAttenuation.z * dist * dist);

		return 1.0;
	}
	return 1.0;
}


// -- returns intensity of reflected ambient lighting
vec3 ambientLighting(){
   return u_matAmbientReflectances * u_lightAmbientIntensitys;
}


// -- returns intensity of diffuse reflection
vec3 diffuseLighting(in vec3 N, in vec3 L){
   return max(dot(N, L), 0.0) * u_matDiffuseReflectances * u_lightDiffuseIntensitys;
}


// -- returns intensity of specular reflection
vec3 specularLightingBlinn(in vec3 N, in vec3 L, in vec3 V){
   float specularTerm = 0;

   if(dot(N, L) > 0){
      // -- half vector
      vec3 H = normalize(L + V);
      specularTerm = CalculateAttenuation() * max(pow(dot(N, H),u_shininess),0.0);
   }

   return specularTerm * u_matSpecularReflectances * u_lightSpecularIntensitys;
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
	resultingColor = BlinnPhong * texture(u_texture, o_textureCoord);
}