#version 330
#define NLIGHTS 1

//-- In values
in vec3 o_position;
in vec3 o_normal;
in vec3 o_toLight;
in vec3 o_toCamera;
in vec2 o_textureCoord;
in float dist;
in vec4 ShadowCoord;

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
uniform sampler2D shadowMap;
uniform samplerCube u_cube_map;
uniform samplerCube cube_shadow;

//-- Out Value
out vec4 resultingColor;



float ShadowCalculation(vec3 fragPos, vec3 lightPos)
{
    // Get vector between fragment position and light position
    vec3 fragToLight = fragPos - lightPos;
    // Use the fragment to light vector to sample from the depth map    
    float closestDepth = texture(cube_shadow, fragToLight).r;
    // It is currently in linear range between [0,1]. Let's re-transform it back to original depth value
    closestDepth *= 20;
    // Now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // Now test for shadows
    float bias = 0.05; // We use a much larger bias since depth is now in [near_plane, far_plane] range
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;

    return shadow;
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


vec3 attenuate(in vec3 N, in vec3 L, in vec3 V, in Light light, in float dist){
    vec3 color = vec3(0.0);
    float NdotL = max(dot(N,L), 0.0);

    if ( light.type.x == 1){
        //-- Directional
        if (NdotL > 0.0){
            float directional = 1.0;
            color += ambientLighting();
            color += directional * diffuseLighting(N, L);
            color += directional * specularLightingBlinn(N, L, V);
        }
    }else if (light.type.y == 1){
        //-- Point Light
        float point_light = 0.0;
        if ( NdotL > 0.0 ){
            point_light = 1.0 / (light.constant + light.linear*dist + light.quadratic*dist*dist);
            color += ambientLighting();
            color += point_light * diffuseLighting(N, L);
            color += point_light * specularLightingBlinn(N, L, V);
        }
    }else if (light.type.z == 1){
        //-- Spot Light
        vec3 spot_dir = vec3(-light.direction.x, light.direction.y, -light.direction.z);
        float theta = dot(normalize(L), normalize(-spot_dir));
        float spot_light = 0.0;
        if ( NdotL > 0.0 )
            if (theta > light.cosCutOff){
                float spot_effect = pow(theta, light.exponent);
                spot_light = spot_effect / (light.constant + light.linear*dist + light.quadratic*dist*dist);
                color += ambientLighting();
                color += spot_light * diffuseLighting(N, L);
                color += spot_light * specularLightingBlinn(N, L, V);
            }
    }

	return color;
}



vec4 calculateBlinnPhong(in vec3 N, in vec3 L, in vec3 V) {
   return vec4(attenuate(N, L, V, u_light[0], dist), 1.0);
} 



void main(void){
    vec3 L = normalize(o_toLight); 
    vec3 N = normalize(o_normal);
    vec3 V = normalize(o_toCamera);

	vec4 BlinnPhong = calculateBlinnPhong(N, L, V);
    float colored = BlinnPhong.x + BlinnPhong.y + BlinnPhong.z;
    if (colored > 0.0) resultingColor = mix(BlinnPhong, texture(u_texture, o_textureCoord), 0.7);
    else resultingColor = vec4(0, 0, 0, 1);

    //-- Solving aliasing problem
    vec2 poissonDisk[4] = vec2[](
        vec2( -0.94201624, -0.39906216 ),
        vec2( 0.94558609, -0.76890725 ),
        vec2( -0.094184101, -0.92938870 ),
        vec2( 0.34495938, 0.29387760 )
    );

    /*float bias = 0.005;
	float visibility = 1.0;
	for (int i=0;i<4;i++){
        if ( texture( shadowMap, ShadowCoord.xy + poissonDisk[i]/700.0 ).z  <  ShadowCoord.z-bias ){
            visibility-=0.2;
        }
    }*/

	float visibility = ShadowCalculation(o_position, u_light[0].position);
    if (colored > 0.0){ 
        //vec4 shadowColor = visibility * resultingColor;
        //resultingColor = mix (resultingColor, shadowColor, 0.6);
        resultingColor = visibility * resultingColor;
    }else resultingColor = vec4(0, 0, 0, 1);
}