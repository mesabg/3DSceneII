#version 330 core
in vec2 Texcoord;
out vec3 outColor;

uniform sampler2D texture1;

void main(){
    outColor = texture(texture1, Texcoord).rgb;
};