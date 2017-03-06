#version 330 core
in layout(location=0) vec3 i_position;

uniform mat4 u_model_matrix;

void main(){
    gl_Position = u_model_matrix * vec4(i_position, 1.0);
}  