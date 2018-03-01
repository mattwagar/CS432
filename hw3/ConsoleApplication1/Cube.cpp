#include "Cube.h"
#define PI 3.14159265

Cube::Cube() {
	// vertices[0] = vec4(-0.5,-0.5,0.5,1);
	// vertices[1] = vec4(-0.5,0.5,0.5,1);
	// vertices[2] = vec4(0.5,0.5,0.5,1);
	// vertices[3] = vec4(0.5,-0.5,0.5,1);
	// vertices[4] = vec4(-0.5,-0.5,-0.5,1);
	// vertices[5] = vec4(-0.5,0.5,-0.5,1);
	// vertices[6] = vec4(0.5,0.5,-0.5,1);
	// vertices[7] = vec4(0.5,-0.5,-0.5,1);

	float angle = 360 / 6;
	cout << "\nangle: " << angle << "\n";
	for(int i = 0; i < 6; i++){

		float x = cos((i) *  angle  *PI/180)/2;
		float y = sin((i) *  angle  *PI/180)/2;

		x = abs(x) <= 1e-004 ? 0 : x; 
		y = abs(y) <= 1e-004 ? 0 : y; 
		
		vertices[i] = vec4(x,y,0.5,1);
		vertices[i+6] = vec4(x,y,-0.5,1);
	}
	for(int i = 0; i < 12; i++)
		cout << i << vertices[i] << "\n";

	buildCube();

	//get buffers for attributes and indices
	glGenBuffers(1, &VBO);

	//put the data on the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

	//set up stuff for the body of the cube
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

Cube::~Cube(){

}

//----------------------------------------------------------------------------
void Cube::makeQuad(int ind1, int ind2, int ind3, int ind4) {
	//triangle #1

	vec4 c1 = randColor();
	vec4 c2 = randColor();

	points[index] = vertices[ind1];
	colors[index] = c1;
	index++;

	points[index] = vertices[ind2];
	colors[index] = c1;
	index++;

	points[index] = vertices[ind3];
	colors[index] = c1;
	index++;

	//Triangle #2
	points[index] = vertices[ind3];
	colors[index] = c2;
	index++;

	points[index] = vertices[ind4];
	colors[index] = c2;
	index++;

	points[index] = vertices[ind1];
	colors[index] = c2;
	index++;

}

void Cube::makeQuad(int ind1, int ind2, int ind3, int ind4, vec4 color) {
	//triangle #1

	points[index] = vertices[ind1];
	colors[index] = color;
	index++;

	points[index] = vertices[ind2];
	colors[index] = color;
	index++;

	points[index] = vertices[ind3];
	colors[index] = color;
	index++;

	//Triangle #2
	points[index] = vertices[ind3];
	colors[index] = color;
	index++;

	points[index] = vertices[ind4];
	colors[index] = color;
	index++;

	points[index] = vertices[ind1];
	colors[index] = color;
	index++;

}

void Cube::buildCube() {
	index = 0;


	makeQuad(0,1,2,3, vec4(0,0,0,1)); // front 1
	makeQuad(0,1,7,6);
	makeQuad(1,2,8,7);
	makeQuad(2,3,9,8);
	makeQuad(6,7,8,9, vec4(0,0,0,1)); // back 1

	makeQuad(3,4,5,0, vec4(0,0,0,1)); // front 2
	makeQuad(3,4,10,9);
	makeQuad(4,5,11,10);
	makeQuad(5,0,6,11);
	makeQuad(9,10,11,6, vec4(0,0,0,1)); // back 2
	
	// makeQuad(1, 0, 3, 2);  //front
	//makeQuad(2, 3, 7, 6);  //right
	//makeQuad(3, 0, 4, 7);  //bottom
	//makeQuad(6, 5, 1, 2);  //top	
	// makeQuad(4, 5, 6, 7);  //back
	//makeQuad(5, 4, 0, 1);  //left
}

void Cube::draw(Camera cam, vector<Light> lights){

	//Draw the cube body
	glBindVertexArray(VAO);
	glUseProgram(program);  //also switch to using this shader program
	glUniformMatrix4fv(mmLoc, 1, GL_TRUE,modelmatrix);
	glDrawArrays(GL_TRIANGLES, 0, 10 * 2 * 3);

}

vec4 Cube::randColor(){
	float r = ((float) rand() / (RAND_MAX));
	float g = ((float) rand() / (RAND_MAX));
	float b = ((float) rand() / (RAND_MAX));
	return vec4(r,g,b,1.0);
}

void circleFace(){}