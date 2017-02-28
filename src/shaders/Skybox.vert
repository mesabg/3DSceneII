#version 330

in layout(location=0) vec3 position;
out vec3 textureCoords;

uniform mat4 u_projection_matrix;
uniform mat4 u_view_matrix;

void main(void){
	mat4 view_matrix = u_view_matrix;
	view_matrix[3][0] = 0;
	view_matrix[3][1] = 0;
	view_matrix[3][2] = 0;
	gl_Position = u_projection_matrix * view_matrix * vec4(position, 1.0);
	textureCoords = position;
}