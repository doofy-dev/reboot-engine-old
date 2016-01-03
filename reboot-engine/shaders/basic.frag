#version 330 core

in vec2 passTextureCoords;
out vec4 color;
uniform vec2 light_pos;
uniform vec4 colour;
uniform sampler2D textureSample;


void main(){	


	color = texture(textureSample, passTextureCoords);
}