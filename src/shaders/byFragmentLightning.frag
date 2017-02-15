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

vec3 specularLightingPhong(in vec3 R, in vec3 V, in vec3 N, in vec3 L){
   float specularTerm = 0;

    if(dot(N, L) > 0){
	   specularTerm = CalculateAttenuation() * max(pow(dot(R, V),u_shininess),0.0);
	}


   return specularTerm * u_matSpecularReflectances * u_lightSpecularIntensitys;
}

vec4 calculatePhong(void) {
   //-- normalize vectors after interpolation
   vec3 L = normalize(o_toLight); 
   vec3 N = normalize(o_normal);
   vec3 V = normalize(o_toCamera);
   vec3 R = normalize(reflect(-L, N));
   vec4 PhongColor;

   //-- get Blinn-Phong reflectance components
   vec3 Iamb = ambientLighting();
   vec3 Idif = diffuseLighting(N, L);
   vec3 Ispe = specularLightingPhong(R, V, N, L);

   //-- combination of all components and diffuse color of the object
   PhongColor.xyz = Iamb + Idif + Ispe;
   PhongColor.a = 1.0;
   return PhongColor;
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


vec4 calculateOrenNayar(){
    const float PI = 3.14159;

    // interpolating normals will change the length of the normal, so renormalize the normal.
	vec3 light = normalize(o_toLight); 
    vec3 normal = normalize(o_normal);
    vec3 eyeDir = normalize(o_toCamera);
    
    // calculate intermediary values
    float NdotL = dot(normal, light);
    float NdotV = dot(normal, eyeDir); 

    float angleVN = acos(NdotV);
    float angleLN = acos(NdotL);
    
    float alpha = max(angleVN, angleLN);
    float beta = min(angleVN, angleLN);
    float gamma = dot(eyeDir - normal * dot(eyeDir, normal), light - normal * dot(light, normal));
    
    float roughnessSquared = u_roughness * u_roughness;
    
    // calculate A and B
    float A = 1.0 - 0.5 * (roughnessSquared / (roughnessSquared + 0.57));

    float B = 0.45 * (roughnessSquared / (roughnessSquared + 0.09));
 
    float C = sin(alpha) * tan(beta);
    
    // put it all together
    float L1 = max(0.0, NdotL) * (A + B * max(0.0, gamma) * C);
    
    // get the final color 
    vec3 finalValue = u_albedo * diffuseLighting(normal, light) * L1;
    return vec4(finalValue, 1.0);
}



vec4 calculateCookTorrance(){
    // set important material values
    float roughnessValue = 0.3; // 0 : smooth, 1: rough
    float k = 1.0 - u_fresnel; // fraction of diffuse reflection (specular reflection = 1 - k)
	vec3 lightDirection = normalize(o_toLight); 
    
    // interpolating normals will change the length of the normal, so renormalize the normal.
    vec3 normal = normalize(o_normal);
    
    // do the lighting calculation for each fragment.
    float NdotL = max(dot(o_normal, lightDirection), 0.0);
    
    float specular = 0.0;
    if(NdotL > 0.0)
    {
        vec3 eyeDir = normalize(o_toCamera);

        // calculate intermediary values
        vec3 halfVector = normalize(lightDirection + eyeDir);
        float NdotH = max(dot(normal, halfVector), 0.0); 
        float NdotV = max(dot(normal, eyeDir), 0.0); // note: this could also be NdotL, which is the same value
        float VdotH = max(dot(eyeDir, halfVector), 0.0);
        float mSquared = u_roughness * u_roughness;
        
        // geometric attenuation
        float NH2 = 2.0 * NdotH;
        float g1 = (NH2 * NdotV) / VdotH;
        float g2 = (NH2 * NdotL) / VdotH;
        float geoAtt = min(1.0, min(g1, g2));
     
        // roughness (or: microfacet distribution function)
        // beckmann distribution function
        float r1 = 1.0 / ( 4.0 * mSquared * pow(NdotH, 4.0));
        float r2 = (NdotH * NdotH - 1.0) / (mSquared * NdotH * NdotH);
        float roughness = r1 * exp(r2);
        
        // fresnel
        // Schlick approximation
        float fresnel = pow(1.0 - VdotH, 5.0);
        fresnel *= (1.0 - u_fresnel);
        fresnel += u_fresnel;
        
        specular = CalculateAttenuation() * ((fresnel * geoAtt * roughness) / (NdotV * NdotL * 3.14));
    }
    
	

    vec3 finalValue = u_lightAmbientIntensitys * NdotL * (k + specular * (1.0 - k));
    return vec4(finalValue, 1.0);
}


float cookTorranceSpecular(
  vec3 lightDirection,
  vec3 viewDirection,
  vec3 surfaceNormal,
  float roughness,
  float fresnel) {

  float VdotN = max(dot(viewDirection, surfaceNormal), 0.0);
  float LdotN = max(dot(lightDirection, surfaceNormal), 0.0);

  //Half angle vector
  vec3 H = normalize(lightDirection + viewDirection);

  //Geometric term
  float NdotH = max(dot(surfaceNormal, H), 0.0);
  float VdotH = max(dot(viewDirection, H), 0.000001);
  float x = 2.0 * NdotH / VdotH;
  float G = min(1.0, min(x * VdotN, x * LdotN));
  
  //Distribution term
  float D = /*beckmannDistribution(NdotH, roughness)*/ vec4(1.0, 1.0, 1.0, 1.0);

  //Fresnel term
  float F = pow(1.0 - VdotN, fresnel);

  //Multiply terms and done
  return  G * F * D / max(3.14159265 * VdotN * LdotN, 0.000001);
}


vec4 calculateCookTorranceNuevo(){
//--- Revisar con calma
/*
  //Light and view geometry
  vec3 viewDirection = normalize(eyePosition - surfacePosition);
  vec3 lightDirection = normalize(lightPosition - surfacePosition);

  //Surface properties
  vec3 normal = normalize(surfaceNormal);

  //Compute specular power
  float power = cookTorranceSpec(
    lightDirection, 
    viewDirection, 
    normal, 
    roughness,
    fresnel);

  gl_FragColor = vec4(power,power,power,1.0);*/
    return vec4(1.0, 1.0, 1.0, 1.0);
}


void main(void){

	vec4 PhongColor = calculatePhong() * u_shadingBitMap[0];
	vec4 BlinnPhong = calculateBlinnPhong() * u_shadingBitMap[1];
	vec4 OrenNayarColor = calculateOrenNayar() * u_shadingBitMap[2];
	vec4 CookTorranceColor = calculateCookTorrance() * u_shadingBitMap[3];

	

	vec4 theColor = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 the_phong = vec4(1.0, 1.0, 1.0, 1.0);

	if(u_shadingBitMap[0] == 1.0)
		the_phong = PhongColor;
	
	if (u_shadingBitMap[1] == 1.0)
		the_phong = BlinnPhong;

	if(u_shadingBitMap[2] == 1.0)
		theColor *= OrenNayarColor;
	
	if(u_shadingBitMap[3] == 1.0)
		theColor *= CookTorranceColor;

	theColor *= the_phong;
	
	//-- Generating color
	
	//vec4 theColor = the_phong + OrenNayarColor + CookTorranceColor;

	//-- Resulting color
	if(u_textureIsActive == 1)
		resultingColor = theColor * texture(u_texture, o_textureCoord);
	else
		resultingColor = theColor;
}