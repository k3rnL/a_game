#version 330 core


layout(location = 0) in vec3 vertex;

out vec2 pos;

void main(){

    gl_Position =  vec4(vertex, 1);
	pos = (vertex.xy * 0.5) + 0.5;
}
