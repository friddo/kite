#version 330
in vec3 in_Quad;
in vec2 in_Tex;
out vec2 ex_Tex;

uniform mat4 model;
uniform mat4 projection;

void main(){
  ex_Tex = in_Tex;
  gl_Position = vec4(in_Quad, 1.0);
}