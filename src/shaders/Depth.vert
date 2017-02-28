#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

// Values that stay constant for the whole mesh.
uniform mat4 depthMVP;
uniform mat4 u_model_matrix;

void main(){
 gl_Position =  depthMVP * u_model_matrix * vec4(vertexPosition_modelspace,1);
}