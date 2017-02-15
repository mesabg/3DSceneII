#version 330

//-- In values
in vec3 o_normal;
in vec3 o_toLight;
in vec3 o_toCamera;
in vec2 o_textureCoord;

//-- parameters of the light
uniform vec3 u_lightAmbientIntensitys; 
uniform vec3 u_lightDiffuseIntensitys; 
uniform vec3 u_lightSpecularIntensitys;

//-- parameters of the material
uniform vec3 u_matAmbientReflectances; 
uniform vec3 u_matDiffuseReflectances; 
uniform vec3 u_matSpecularReflectances; 

//-- Variables
uniform float u_shininess; 
uniform sampler2D u_texture;

//-- Out Value
out vec4 resultingColor;

// -- returns intensity of reflected ambient lighting
vec3 ambientLighting(){
   return u_matAmbientReflectances * u_lightAmbientIntensitys;
}

// -- returns intensity of diffuse reflection
vec3 diffuseLighting(in vec3 N, in vec3 L){
   return max(dot(N, L), 0.0) * u_matDiffuseReflectances * u_lightDiffuseIntensitys;
}

// -- returns intensity of specular reflection
vec3 specularLighting(in vec3 N, in vec3 L, in vec3 V){
   float specularTerm = 0;

   if(dot(N, L) > 0){
      // -- half vector
      vec3 H = normalize(L + V);
      specularTerm = max(pow(dot(N, H),u_shininess),0.0);
   }

   return specularTerm * u_matSpecularReflectances * u_lightSpecularIntensitys;
}

void main(void) {
   //-- normalize vectors after interpolation
   vec3 L = normalize(o_toLight); 
   vec3 N = normalize(o_normal);
   vec3 V = normalize(o_toCamera);
   vec3 R = normalize(reflect(L, N));
   vec4 PhongColor;

   //-- get Blinn-Phong reflectance components
   vec3 Iamb = ambientLighting();
   vec3 Idif = diffuseLighting(N, L);
   vec3 Ispe = specularLighting(N, L, V);

   //-- combination of all components and diffuse color of the object
   PhongColor.xyz = Iamb + Idif + Ispe;
   PhongColor.a = 1.0;
   resultingColor = PhongColor + texture(u_texture, o_textureCoord);
} 