#version 330 core

uniform vec4 color;
uniform sampler2D font;
uniform vec4 view;
out vec4 color_out;

in vec2 pos;

void main(){
  color_out = vec4(1, 1, 1, texture2D(font, pos.xy).r) * color * view;
}
