#version 330 core

layout (location = 1) in vec2 textureCoords;

out vec4 color;


//uniform vec4 colour;
uniform vec2 light_pos;
uniform sampler2D diffuse;

in vec4 o_color;
in vec4 vpos;

void main(){

	float intensity = 1.0 / length(vpos.xy-light_pos);

	color = o_color*intensity;
//	color = texture(diffuse, textureCoords) * intensity;
}