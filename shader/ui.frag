#version 330 core

uniform vec4 color;
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
  color_out = color * 0;
  // return;
  vec2 uv = varying_uv;
  // uv += 0.5;
  float value = roundedFrame((uv-0.5) * dimension, 150);
  //value = roundedFrame(gl_FragCoord.xy, vec2(1), 0.25, 0.1);
  // if (value < 0.1)
    color_out = vec4(color.xyz, value+0);
  // color_out = vec4(abs(uv-0.5), 0, 1);

  //color_out = vec4(uv.xy, 0, 1);
}
