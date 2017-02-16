#version 330

in layout(location=0) vec3 i_position;
in layout(location=1) vec2 i_texture;
in layout(location=2) vec3 i_normal;


//-- Input values
in vec2 o_textureVert;
in vec3 o_normalVert;
in vec4 worldPosition;


//-- Vectores
uniform vec3 u_lightPosition;
uniform vec3 eye_position;

//-- Matrices
uniform mat4 u_viewMat;
uniform mat4 u_normalMat;
uniform mat4 u_projMat;
uniform mat4 u_modelMat;

//-- Attributes
out vec3 o_normal;
out vec3 o_toLight;
out vec3 o_toCamera;
out vec2 o_textureCoord;

out vec3 diffuse, ambient;
out float dist;


//-- parameters of the light
uniform vec3 u_lightAmbientIntensitys; 
uniform vec3 u_lightDiffuseIntensitys; 
uniform vec3 u_lightSpecularIntensitys;

//-- parameters of the material
uniform vec3 u_matAmbientReflectances; 
uniform vec3 u_matDiffuseReflectances; 
uniform vec3 u_matSpecularReflectances; 



void main(void){
	vec4 worldPosition2 = u_modelMat * vec4(i_position, 1.0);


	//-- normal in world space
	o_normal =  vec3( normalize(  u_modelMat * vec4(i_normal, 0.0)) );

	//direction to light
	vec3 VP;
	VP = u_lightPosition  - worldPosition.xyz;
	o_toLight = normalize(VP); 
	dist = length(VP);

	//-- Diffuse, Ambient and Ambient Global values
	diffuse = u_matDiffuseReflectances * u_lightDiffuseIntensitys;
	ambient = u_matAmbientReflectances * u_lightAmbientIntensitys;

	//direction to camera
	o_toCamera = normalize( eye_position - worldPosition.xyz );

	//-- screen space coordinates of the vertex
	o_textureCoord = i_texture;
	gl_Position = u_projMat * u_viewMat * worldPosition;
} 
