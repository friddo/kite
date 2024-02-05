#version 330
in vec3 in_Quad;
in vec2 in_Tex;
out vec2 ex_Tex;

uniform mat4 model;
uniform mat4 projection;

void main(){
  gl_Position = projection*model*vec4(in_Quad, 1.0);
  ex_Tex = in_Tex;
}