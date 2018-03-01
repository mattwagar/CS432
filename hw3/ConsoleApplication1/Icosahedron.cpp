#include "Icosahedron.h"
#define PI 3.14159265

Icosahedron::Icosahedron() {
	vertices[0] = vec4(.00000, .85065, .52573, 1);
	vertices[1] = vec4(.85065, .52573, -.00000, 1);
	vertices[2] = vec4(.00000, .85065, -.52573, 1);
	vertices[3] = vec4(.52573, .00000, -.85065, 1);
	vertices[4] = vec4(-.52573, .00000, -.85065, 1);
	vertices[5] = vec4(-.85065, .52573, -.00000, 1);
	vertices[6] = vec4(-.52573, .00000, .85065, 1);
	vertices[7] = vec4(.52573, .00000, .85065, 1);
	vertices[8] = vec4(.85065, -.52573, .00000, 1);
	vertices[9] = vec4(.00000, -.85065, .52573, 1);
	vertices[10] = vec4(.00000, -.85065, -.52573, 1);
	vertices[11] = vec4(-.85065, -.52573, .00000, 1);

	for(int i = 0; i < 12; i++)
		cout << i << vertices[i] << "\n";

	buildIcosahedron();

	

	//get buffers for attributes and indices
	glGenBuffers(1, &VBO);
	//initialize index buffer
	glGenBuffers(1, &VIO);

	//put the data on the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors) + sizeof(colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VIO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices)  + sizeof(frameIndices), NULL, GL_STATIC_DRAW);
	//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);
	//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), sizeof(frameIndices), frameIndices);

	//set up stuff for the body of the Icosahedron
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); //make this VAO active
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //associate the VBO with the active VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VIO);  //associate the VBO with the active VAO
	
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
	assert((viewLoc = glGetUniformLocation(program, "view_matrix")) != -1);
	assert((projLoc = glGetUniformLocation(program, "proj_matrix")) != -1);

	glGenVertexArrays(1, &frameVAO);
	glBindVertexArray(frameVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VIO);
	assert((program2 = InitShader("vshader00_v150.glsl", "fshader01_v150.glsl"))!=-1);
	glUseProgram(program2); //make it the active one
	assert((vPosition = glGetAttribLocation(program2, "vPosition")) != -1);
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	assert((vColor = glGetUniformLocation(program2, "color")) != -1);
	
}

void Icosahedron::drawLines(){
	vec4 indices[12];

	GLubyte frameIndices[30*2] = { 0,1,
								   1,2,
								   2,0,
								   2,3,
								   3,1,
								   2,4,
								   3,4,
								   4,5,
								   5,2,
								   0,5,
								   7,0,
								   0,6,
								   6,7,
								   3,8,
								   8,1,
								   1,7,
								   7,8,
								   4,10,
								   10,3,
								   5,11,
								   11,4,
								   10,11,
								   5,6,
								   6,9,
								   9,11,
								   11,6,
								   7,9,
								   8,9,
								   9,10,
								   8,10};

	for(int i = 0; i < 12; i++ ){
		indices[i] = Scale(1.001)* vertices[i];
	}

	glLineWidth(5.0);

	glBegin(GL_LINES);
	glColor3f( 0.0f, 0.0f, 0.0f);
	for(int i = 0; i < 60; i+=2){
		glVertex4f(indices[frameIndices[i]][0], indices[frameIndices[i]][1], indices[frameIndices[i]][2], indices[frameIndices[i]][3]);
		glVertex4f(indices[frameIndices[i+1]][0], indices[frameIndices[i+1]][1], indices[frameIndices[i+1]][2], indices[frameIndices[i+1]][3]);
	}

	glEnd();


}

Icosahedron::~Icosahedron(){

}

//----------------------------------------------------------------------------
void Icosahedron::makeQuad(int ind1, int ind2, int ind3, int ind4) {
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

void Icosahedron::makeQuad(int ind1, int ind2, int ind3, int ind4, vec4 color) {
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

void Icosahedron::makeTri(int ind1, int ind2, int ind3) {
	//triangle #1

	vec4 c1 = randColor();

	points[index] = vertices[ind1];
	colors[index] = c1;
	index++;

	points[index] = vertices[ind2];
	colors[index] = c1;
	index++;

	points[index] = vertices[ind3];
	colors[index] = c1;
	index++;
}

void Icosahedron::buildIcosahedron() {
	index = 0;
	makeTri(0,1,2);
	makeTri(1,2,3);
	makeTri(2,3,4);
	makeTri(2,4,5);
	makeTri(2,0,5);
	
	makeTri(0,1,7);
	makeTri(0,6,7);
	makeTri(1,3,8);
	makeTri(1,7,8);
	makeTri(3,4,10);
	makeTri(3,8,10);
	makeTri(4,5,11);
	makeTri(4,10,11);
	makeTri(5,6,11);
	makeTri(0,5,6);

	makeTri(6,9,11);
	makeTri(6,7,9);
	makeTri(7,8,9);
	makeTri(8,9,10);
	makeTri(9,10,11);

		//2,9,11,3,4,7,8,     
		//6,5
		//0,1,10
	
}

void Icosahedron::draw(Camera cam, vector<Light> lights){

	//Draw the Icosahedron body
	glBindVertexArray(VAO);
	glUseProgram(program);  //also switch to using this shader program
	glUniformMatrix4fv(mmLoc, 1, GL_TRUE,modelmatrix);
	glUniformMatrix4fv(viewLoc, 1, GL_TRUE,cam.getCameraMatrix());
	glUniformMatrix4fv(projLoc, 1, GL_TRUE,cam.getProjMatrix());
	glDrawArrays(GL_TRIANGLES, 0, 12 * 2 * 3);

	// //Draw the cube frame
	// glBindVertexArray(frameVAO);
	// glUseProgram(program2); //also switch to using this shader program
	// GLuint mm2;
	// assert((mm2 = glGetUniformLocation(program2, "model_matrix")) != -1);
	// glUniformMatrix4fv(mm2, 1, GL_TRUE, modelmatrix);
	// glUniformMatrix4fv(viewLoc, 1, GL_TRUE,cam.getCameraMatrix());
	// glUniformMatrix4fv(projLoc, 1, GL_TRUE,cam.getProjMatrix());

	// //cout << "view matrix" << "\n" << cam.getCameraMatrix() << "\n";
	// //cout << "proj matrix" << "\n" <<  cam.getProjMatrix() << "\n";
	// glUniform4fv(vColor, 1, vec4(0, 0, 0, 1));
	// glLineWidth(5.0);
	// glDrawElements(GL_LINES, 60, GL_UNSIGNED_BYTE, BUFFER_OFFSET(sizeof(vertices)));

	drawLines();


}

vec4 Icosahedron::randColor(){
	float r = ((float) rand() / (RAND_MAX));
	float g = ((float) rand() / (RAND_MAX));
	float b = ((float) rand() / (RAND_MAX));
	return vec4(r,g,b,1.0);
}

void circleFace(){}