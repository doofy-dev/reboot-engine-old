#version 330 core

in vec2 passTextureCoords;


uniform vec2 light_pos;
uniform vec4 colour;
uniform sampler2D textureSample;
uniform vec4 face_color = vec4(0,0,0,0);
uniform int use_color = 0;

out vec4 color;

void main(){	
	if(use_color==0){
		color = texture(textureSample, passTextureCoords);
	}else{
		color = face_color;
	}
}