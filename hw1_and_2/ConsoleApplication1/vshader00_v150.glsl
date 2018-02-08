#version 150

in vec3 vPosition;
in vec4 vColor;
uniform mat3 model_matrix;
uniform mat3 inverse_trans;
out vec4 fcolor;



void main() 
{ 
	fcolor = vColor;

	mat3 t = inverse_trans;

	t[2][0] *= -1;
	t[2][1] *= -1;
	
	gl_Position = vec4((t*model_matrix*inverse_trans*vPosition).xy,0,1);
}