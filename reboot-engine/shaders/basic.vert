#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normals;

uniform struct{
	mat4 model;
	mat4 view;
	mat4 projection;
} mvp;



out vec2 passTextureCoords;

void main(){
	passTextureCoords = textureCoords;
	gl_Position = mvp.projection  * mvp.view * mvp.model * vec4(position,1);

}