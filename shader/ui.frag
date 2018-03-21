#version 330 core

uniform vec4 color;
uniform int corner;
uniform vec2 dimension;

out vec4 color_out;
in vec2 varying_uv;

float roundedFrame (vec2 pos,float radius)
{
  pos = abs(pos);
  vec2 corner_center = abs(dimension - radius) - dimension / 2;
  if (pos.x < corner_center.x || pos.y < corner_center.y)
    return (1.);
  // return (0.);
  float value = length(distance(pos, corner_center));
  // return value*1.5;
  return (smoothstep(value-0.75, value+0.75, radius));
  if (value < radius)
    return (1.);
  return (0.);
}

void main(){
  color_out = color;

  if (corner > 0) {
	vec2 uv = varying_uv;
	float value = roundedFrame((uv-0.5) * dimension, corner);
	color_out = vec4(color.xyz, value+0);
  }
}
