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

//-- Out Values (After some calculations)
in vec3 o_position;
in vec3 o_position_tangent;
in vec3 o_normal;
in vec3 o_view;
in vec3 o_view_tangent;
in Light o_light[NLIGHTS];
in vec2 o_texture_coord;
in vec4 o_shadow_coord;
in vec3 reflectedVector;
in vec3 refractedVector;
in mat3 TBN;

//-- Constant in variables
uniform Light u_light[NLIGHTS];
uniform Attenuation u_attenuation[NLIGHTS];
uniform Material u_material;
uniform int u_texture_state;
uniform int u_normal_mapped;
uniform int u_is_reflected;
uniform int u_is_refracted;
uniform int u_parallax_mapped;
uniform float u_parallax_factor;
uniform sampler2D u_texture;
uniform sampler2D u_shadow_map;
uniform sampler2D u_normal_texture;
uniform samplerCube u_cube_map;
uniform samplerCube u_cube_shadow_map;

//-- Out Value
out vec4 resultingColor;

float omnidirectionalShadowCalculation(vec3 fragPos, vec3 lightPos){
    vec3 fragToLight = fragPos - lightPos; 
    float closestDepth = texture(u_cube_shadow_map, fragToLight).r;
    closestDepth *= 20;
    float currentDepth = length(fragToLight);
    float bias = 0.05;
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;
    return shadow;
}


float directionalShadowCalculation(in sampler2D shadow_map, in vec4 shadow_coords){
    //-- Solving aliasing problem
    vec2 poissonDisk[4] = vec2[](
        vec2( -0.94201624, -0.39906216 ),
        vec2( 0.94558609, -0.76890725 ),
        vec2( -0.094184101, -0.92938870 ),
        vec2( 0.34495938, 0.29387760 )
    );

    float bias = 0.005;
	float shadow = 1.0;
	for (int i=0;i<4;i++)
        if ( texture( shadow_map, shadow_coords.xy + poissonDisk[i]/700.0 ).z  <  shadow_coords.z-bias )
            shadow-=0.24;
    return shadow;
}


// -- returns intensity of reflected ambient lighting
vec3 ambientLighting(Light light, Material material){
	return material.ambient * light.ambient;
}


// -- returns intensity of diffuse reflection
vec3 diffuseLighting(in vec3 N, in vec3 L, Light light, Material material){
   return max(dot(N, L), 0.0) * material.diffuse * light.diffuse;
}


// -- returns intensity of specular reflection
vec3 specularLightingBlinn(in vec3 N, in vec3 L, in vec3 V, Light light, Material material){
   float specularTerm = 0;

   if(dot(N, L) > 0){
      // -- half vector
      vec3 H = normalize(L + V);
      specularTerm = max(pow(dot(N, H), material.shininess),0.0);
   }

   return specularTerm * material.specular * light.specular;
}

vec3 BlinnPhongDirectional(in vec3 N, in vec3 L, in vec3 V, in Light light, in Attenuation attenuation, in Material material){
    vec3 color = vec3(0.0); 

    //-- Directional Light calculations
    float directional = 1.0;
    float shadow = directionalShadowCalculation(u_shadow_map, o_shadow_coord);
    color += ambientLighting(light, material);
    color += shadow * directional * diffuseLighting(N, L, light, material);
    color += shadow * directional * specularLightingBlinn(N, L, V, light, material);

    return color;
}

vec3 BlinnPhongPoint(in vec3 N, in vec3 L, in vec3 V, in Light light, in Attenuation attenuation, in Material material){
    vec3 color = vec3(0.0); 

    //-- Point Light Calculations
    float point_light = 1.0 / (attenuation.constant + attenuation.linear*light.dist + attenuation.quadratic*light.dist*light.dist);
    float shadow = directionalShadowCalculation(u_shadow_map, o_shadow_coord);
    color += ambientLighting(light, material);
    color += point_light * diffuseLighting(N, L, light, material);
    color += point_light * specularLightingBlinn(N, L, V, light, material);

    return shadow * color;
}

vec3 BlinnPhongSpot(in vec3 N, in vec3 L, in vec3 V, in Light light, in Attenuation attenuation, in Material material, in int type){
    vec3 color = vec3(0.0); 

    //-- SpotLight Calculations
    vec3 spot_dir = vec3(-attenuation.direction.x, attenuation.direction.y, -attenuation.direction.z);
    if (type == 1 || type == 2) spot_dir = TBN * spot_dir;
    float theta = dot(normalize(L), normalize(-spot_dir));
    float epsilon = (attenuation.inner_cosine - attenuation.outer_cosine);
    float intensity = clamp((theta - attenuation.outer_cosine) / epsilon, 0.0, 1.0);
    if (theta > attenuation.inner_cosine){
        float spot_effect = pow(theta, attenuation.exponent);
        float spot_light = spot_effect / (attenuation.constant + attenuation.linear*light.dist + attenuation.quadratic*light.dist*light.dist);
        //float shadow = directionalShadowCalculation(u_shadow_map, o_shadow_coord);
        color += ambientLighting(light, material);
        color += spot_light * diffuseLighting(N, L, light, material);
        color += spot_light * specularLightingBlinn(N, L, V, light, material);
    }
    float shadow = directionalShadowCalculation(u_shadow_map, o_shadow_coord);

    return shadow * color;
}

vec4 calculateBlinnPhong(in vec3 N, in vec3 L, in vec3 V, in Light light, in Attenuation attenuation, in Material material, in int index) {
    float NdotL = max(dot(N,L), 0.0);
    if (NdotL > 0.0){
        if (u_light[index].type.x == 1) return vec4(BlinnPhongDirectional(N, L, V, light, attenuation, material), 1);
        else if (u_light[index].type.y == 1) return vec4(BlinnPhongPoint(N, L, V, light, attenuation, material), 1);
        else if (u_light[index].type.z == 1) return vec4(BlinnPhongSpot(N, L, V, light, attenuation, material, u_parallax_mapped + u_normal_mapped), 1);
    }
    return vec4(0, 0, 0, 1);
} 

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir){ 
    float height =  texture(u_shadow_map, texCoords).r;    
    vec2 p = viewDir.xy / viewDir.z * (height * u_parallax_factor);
    return texCoords - p;    
} 

void main(void){
    vec3 L; 
    vec3 N;
    vec3 V;
    vec4 color = vec4(0.0);
    vec2 texture_coord;

    for (int i=0; i<NLIGHTS; i++){
        if (u_normal_mapped == 1){
            if (u_light[i].type.x == 1) L = normalize(o_light[i].position_tangent); 
            else L = normalize(o_light[i].direction_tangent);
            N = normalize(( (2.0 * texture(u_normal_texture, o_texture_coord, -1.0) - 1.0).xyz ));
            V = normalize(o_view_tangent);
            texture_coord = o_texture_coord;
        }else if (u_parallax_mapped == 1){
            if (u_light[i].type.x == 1) L = normalize(o_light[i].position_tangent); 
            else L = normalize(o_light[i].direction_tangent);
            N = normalize(( (2.0 * texture(u_normal_texture, o_texture_coord, -1.0) - 1.0).xyz ));
            V = normalize(o_view_tangent);
            texture_coord = ParallaxMapping(o_texture_coord, normalize(o_view_tangent - o_position_tangent));
        }else{
            if (u_light[i].type.x == 1) L = normalize(o_light[i].position); 
            else L = normalize(o_light[i].direction);
            N = normalize(o_normal);
            V = normalize(o_view);
            texture_coord = o_texture_coord;
        }
        color += calculateBlinnPhong(N, L, V, o_light[i], u_attenuation[i], u_material, i);
    }

    float colored = color.x + color.y + color.z;
    if (colored > 0.0)
        if ( u_texture_state == 1) resultingColor = mix(color, texture(u_texture, texture_coord), 0.7);
        else resultingColor = color;
    else resultingColor = vec4(0, 0, 0, 1);

    vec4 reflectedColor;
	vec4 refractedColor;
    if (colored > 0.0)
        if (u_is_reflected==1 && u_is_refracted==1){
            reflectedColor = texture(u_cube_map, reflectedVector);
            refractedColor = texture(u_cube_map, refractedVector);
            vec4 enviroColor = mix(reflectedColor, refractedColor, 0.5);
            resultingColor = mix(resultingColor, enviroColor, 1.0);
            //resultingColor = enviroColor;
        }else if (u_is_reflected==1){
            reflectedColor = texture(u_cube_map, reflectedVector);
            resultingColor = mix(resultingColor, reflectedColor, 0.5);
            //resultingColor = reflectedColor;
        }else if (u_is_refracted==1){
            refractedColor = texture(u_cube_map, refractedVector);
            resultingColor = mix(resultingColor, refractedColor, 0.5);
            //resultingColor = refractedColor;
        } 
}