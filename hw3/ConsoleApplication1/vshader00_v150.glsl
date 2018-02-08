#version 150

in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;
uniform mat4 model_matrix;

void main() 
{ 

  gl_Position = model_matrix*vPosition;
  color = vColor;
 

}