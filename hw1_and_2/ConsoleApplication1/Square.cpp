#include "Square.h"

Square::Square() {
	vec4 vRgba = vec4(0.0, 0.0, 1.0, 1.0);
	vertices.push_back(Vertex(vec3(0.25, 0.25, 1),vRgba)); 
	vertices.push_back(Vertex(vec3(0.75, 0.25, 1),vRgba));
	vertices.push_back(Vertex(vec3(0.75, 0.75, 1),vRgba));
	vertices.push_back(Vertex(vec3(0.25, 0.75, 1),vRgba));
	init();
}

Square::Square(vec4 _rgba) {
	vertices.push_back(Vertex(vec3(0.25, 0.25, 1),_rgba)); 
	vertices.push_back(Vertex(vec3(0.75, 0.25, 1),_rgba));
	vertices.push_back(Vertex(vec3(0.75, 0.75, 1),_rgba));
	vertices.push_back(Vertex(vec3(0.25, 0.75, 1),_rgba));
	init();
}

Square::Square(vec4 _rgba, vec3 _pos1, vec3 _pos2, vec3 _pos3, vec3 _pos4){
	vertices.push_back(Vertex(_pos1,_rgba));
	vertices.push_back(Vertex(_pos2,_rgba));
	vertices.push_back(Vertex(_pos3,_rgba));
	vertices.push_back(Vertex(_pos4,_rgba));
	init();
	
}

Square::Square(vec3 _pos1, vec3 _pos2, vec3 _pos3, vec3 _pos4){
	vertices.push_back(Vertex(_pos1,randColor()));
	vertices.push_back(Vertex(_pos2,randColor()));
	vertices.push_back(Vertex(_pos3,randColor()));
	vertices.push_back(Vertex(_pos4,randColor()));
	init();
}



Square::~Square() {
	//put additional things to destroy in here.  The Drawable class handles the VBO/VAO
}

void Square::init(){
	theta = 0;
	//get a vertex buffer and a vertex array object
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO); //make this VAO active
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //associate the VBO with the active VAO

	//now make the data and put it on the vertex buffer
	// Vertices of a unit cube centered at origin, sides aligned with axes
	

	

	//cout << "SIZE OF Square" << sizeof(points) << "\n";
	//put the data on the VBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, &vertices[0], GL_DYNAMIC_DRAW);

	//Now let's set up the shaders!!
	// Load shaders
	assert((program = InitShader("vshader00_v150.glsl", "fshader00_v150.glsl"))!=-1);
	glUseProgram(program);  //make it the active one

	//get the location of the vPosition attribute
	assert((vPosition = glGetAttribLocation(program, "vPosition")) != -1);
	glEnableVertexAttribArray(vPosition);  //enable it
	//associate the area in the active VBO with this attribute and tell it how data to pull out for each vertex from the VBO
	//glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	assert((vColor = glGetAttribLocation(program, "vColor")) != -1);
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
	//get the location of the uniform color in the shader
	//assert((vColor = glGetUniformLocation(program, "color"))!=-1);
}

void Square::draw(Camera cam, vector<Light> lights){
	//make this object's VAO active
	//this in turn makes it's associate VBO active
	//and the attributes links to the shader
	glBindVertexArray(VAO); 
	glUseProgram(program);  //also switch to using this shader program
	
	float rangle = theta*2.0*3.14 / 360;
	float c = cos(rangle);
	float s = sin(rangle);

	mat3 it = mat3( vec3(1, 0, (vertices[0].position.x + vertices[2].position.x)/-2),
					   vec3(0, 1, (vertices[0].position.y + vertices[2].position.y)/-2),
					   vec3(0, 0, 1));
	
	mat3 rot = mat3( vec3(c, -s, 0),
					 vec3(s, c, 0),
					 vec3(0, 0, 1));

	assert((inverse_trans = glGetUniformLocation(program, "inverse_trans"))!=-1);
	glUniformMatrix3fv(inverse_trans,1, GL_TRUE,it);

	assert((model_matrix = glGetUniformLocation(program, "model_matrix"))!=-1);
	glUniformMatrix3fv(model_matrix,1, GL_TRUE,rot);


	//unfortunately, every time we draw we still need to set again all uniform variables
	//vec4 rgba = vec4(0.0, 0.0, 1.0, 1.0);// RGBA colors
	//glUniform4fv(vColor, 1, vRgba);

	//now that we're all set up, the the GPU to render NumVertice vertexes as a Square fan
	//starting at offset 0 in the VBO
	glDrawArrays(GL_TRIANGLE_FAN, 0, NumVertices);

}

void Square::rotate(){
	

	theta+=1;
	if(theta > 360) theta = 0;

	float rangle = theta*2.0*3.14 / 360;
	float c = cos(rangle);
	float s = sin(rangle);

	vector<Vertex> verts = vertices;

	for (unsigned int i = 0; i < NumVertices; i++){
		verts[i].color = verts[i].color * abs(c);
	}
	//put the data on the VBO

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //associate the VBO with the active VAO
	glUseProgram(program);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, &verts[0], GL_DYNAMIC_DRAW);

	//glDrawArrays(GL_TRIANGLE_FAN, 0, NumVertices);
}

vec4 Square::randColor(){
	float r = ((float) rand() / (RAND_MAX));
	float g = ((float) rand() / (RAND_MAX));
	float b = ((float) rand() / (RAND_MAX));
	return vec4(r,g,b,1.0);
}
