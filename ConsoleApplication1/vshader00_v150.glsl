#version 150

in vec2 vPosition;



void main() 
{ 
  gl_Position = vec4(vPosition.x, vPosition.y, 0, 1);
}