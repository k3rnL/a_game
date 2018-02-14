#version 330 core

uniform int id;

layout(location = 0) out vec3 color;

void main() 
{
float a = id;
	color = vec3(a/256);
	return;
}