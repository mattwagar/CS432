#version 150

in vec3 vPosition;
in vec4 vColor;
uniform mat3 model_matrix;
out vec4 fcolor;



void main() 
{ 
	fcolor = vColor;
	mat3 itrans;
	itrans[0] = vec3(1,0,-vPosition.x);
	itrans[1] = vec3(0,1,-vPosition.y);
	itrans[2] = vec3(0,0,1);
	
	mat3 trans;
	trans[0] = vec3(1,0,vPosition.x);
	trans[1] = vec3(0,1,vPosition.y);
	trans[2] = vec3(0,0,1);
	
	gl_Position = vec4((model_matrix*itrans*vPosition).xy,0,1);
}