#version 330

in layout(location=0) vec3 i_position;
in layout(location=1) vec2 i_texture;
in layout(location=2) vec3 i_normal;

//-- Uniforms
uniform mat4 u_modelMat;

//-- Out
out vec2 o_textureVert;
out vec3 o_normalVert;
out vec4 worldPosition;


void main(void){
	worldPosition = u_modelMat * vec4(i_position, 1.0);

	//-- Saving Values
	o_textureVert = i_texture;
	o_normalVert = i_normal;
} 


