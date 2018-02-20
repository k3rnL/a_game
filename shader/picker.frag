#version 330 core

uniform int id;

layout(location = 0) out uvec3 color;

void main() 
{
float a = id;
	color = uvec3(0);
	color.x = uint((id & 0xff0000) >> 16);
	color.y = uint((id & 0x00ff00) >>  8);
	color.z = uint((id & 0x0000ff) >>  0);
	return;
}