#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normals;

uniform mat4 pr_matrix= mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix;

out vec2 passTextureCoords;

void main(){
	passTextureCoords = textureCoords;
	gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(position,1);

}