#version 150

in vec2 vPosition;
in vec4 vColor;
out vec4 fcolor;


void main() 
{ 
	fcolor = vColor;
	gl_Position = vec4(vPosition.x, vPosition.y, 0, 1);
}