#version 330

in vec3 textureCoords;
out vec4 out_color;

uniform samplerCube u_cube_map;

void main(void){
	out_color = texture(u_cube_map, textureCoords);
}