#include "Polyhedron.h"

Polyhedron::Polyhedron() {
	vertices[0] = vec4(-0.5,-0.5,0.5,1);
	vertices[1] = vec4(-0.5,0.5,0.5,1);
	vertices[2] = vec4(0.5,0.5,0.5,1);
	vertices[3] = vec4(0.5,-0.5,0.5,1);
	vertices[4] = vec4(-0.5,-0.5,-0.5,1);
	vertices[5] = vec4(-0.5,0.5,-0.5,1);
	vertices[6] = vec4(0.5,0.5,-0.5,1);
	vertices[7] = vec4(0.5,-0.5,-0.5,1);
	potentialColors[0] = randColor();
	potentialColors[1] = randColor();
	potentialColors[2] = randColor();
	potentialColors[3] = randColor();
	potentialColors[4] = randColor();
	potentialColors[5] = randColor();
	potentialColors[6] = randColor();
	potentialColors[7] = randColor();

	buildPolyhedron();

	//get buffers for attributes and indices
	glGenBuffers(1, &VBO);

	//put the data on the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

	//set up stuff for the body of the Polyhedron
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); //make this VAO active
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //associate the VBO with the active VAO

	assert((program = InitShader("vshader00_v150.glsl", "fshader00_v150.glsl"))!=-1);
	glUseProgram(program);  //make it the active one

	assert((vPosition = glGetAttribLocation(program, "vPosition")) != -1);
	glEnableVertexAttribArray(vPosition);  //enable it
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	//get the location of the uniform color in the shader
	assert((vColor = glGetAttribLocation(program, "vColor"))!=-1);
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));

	//get the location of the model matrix
	assert((mmLoc = glGetUniformLocation(program, "model_matrix")) != -1);

}

Polyhedron::~Polyhedron(){

}

//----------------------------------------------------------------------------
void Polyhedron::makeQuad(int ind1, int ind2, int ind3, int ind4) {
	//triangle #1
	points[index] = vertices[ind1];
	colors[index] = potentialColors[index%8];
	index++;

	points[index] = vertices[ind2];
	colors[index] = colors[index - 1];
	index++;

	points[index] = vertices[ind3];
	colors[index] = colors[index - 1];
	index++;

	//Triangle #2
	points[index] = vertices[ind3];
	colors[index] = colors[index - 1];
	index++;

	points[index] = vertices[ind4];
	colors[index] = colors[index - 1];
	index++;

	points[index] = vertices[ind1];
	colors[index] = colors[index - 1];
	index++;
}

void Polyhedron::buildPolyhedron() {
	index = 0;

	makeQuad(1, 0, 3, 2);  //front
	makeQuad(2, 3, 7, 6);  //right
	makeQuad(3, 0, 4, 7);  //bottom
	makeQuad(6, 5, 1, 2);  //top
	makeQuad(4, 5, 6, 7);  //back
	makeQuad(5, 4, 0, 1);  //left
}

void Polyhedron::draw(Camera cam, vector<Light> lights){

	//Draw the Polyhedron body
	glBindVertexArray(VAO);
	glUseProgram(program);  //also switch to using this shader program
	glUniformMatrix4fv(mmLoc, 1, GL_TRUE,modelmatrix);
	glDrawArrays(GL_TRIANGLES, 0, 6 * 2 * 3);

}

vec4 Polyhedron::randColor(){
	float r = ((float) rand() / (RAND_MAX));
	float g = ((float) rand() / (RAND_MAX));
	float b = ((float) rand() / (RAND_MAX));
	return vec4(r,g,b,1.0);
}