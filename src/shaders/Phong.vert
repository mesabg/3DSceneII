#version 330

in layout(location=0) vec3 i_position;
in layout(location=1) vec2 i_texture;
in layout(location=2) vec3 i_normal;

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

void main(void){
	vec4 worldPosition = vec4(i_position, 1.0);

	//-- normal in world space
	o_normal = normalize( vec3(u_normalMat * vec4(i_normal, 0.0)) );

	//direction to light
	o_toLight = normalize( u_lightPosition - worldPosition.xyz ); 

	//direction to camera
	o_toCamera = normalize( eye_position - worldPosition.xyz );

	//-- screen space coordinates of the vertex
	o_textureCoord = i_texture;
	gl_Position = u_projMat * u_viewMat * u_modelMat * worldPosition;
} 


