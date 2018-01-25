#include "Circle.h"
#define PI 3.14159265


Circle::Circle() {
	vRgba = vec4(0.0, 1.0, 0.0, 1.0);
	NumVertices = 41;
	init();
}

Circle::Circle(vec4 _rgba) {
	vRgba = _rgba;
	init();
}

Circle::~Circle() {
	//put additional things to destroy in here.  The Drawable class handles the VBO/VAO
}

void Circle::init(){
	//get a vertex buffer and a vertex array object
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO); //make this VAO active
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //associate the VBO with the active VAO

	//now make the data and put it on the vertex buffer
	// Vertices of a unit cube centered at origin, sides aligned with axes
	//vec2 *verts = new vec2[NumVertices];

	vector<Vertex> verts(NumVertices);

	verts[0] = Vertex(vec2(0,0), randColor()); 
	float angle = NumVertices-1 == 0 ? 360 : 360 / (NumVertices-1);
	cout << "\nangle: " << angle << "\n";
	for(int i = 1; i < NumVertices; i++){

		float x = cos((i-1) *  angle  *PI/180)/5;
		float y = sin((i-1) *  angle  *PI/180)/5;

		x = abs(x) <= 1e-004 ? 0 : x; 
		y = abs(y) <= 1e-004 ? 0 : y; 
		
		verts[i] = Vertex(vec2(x,y), randColor());
		cout <<		vec2(x,y) << "\n";
	}
	verts.push_back(verts[1]);
	NumVertices++;


	//cout << "SIZE OF SQUARE" << sizeof(points) << "\n";
	//put the data on the VBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * NumVertices, &verts[0], GL_STATIC_DRAW);

	//Now let's set up the shaders!!
	// Load shaders
	assert((program = InitShader("vshader00_v150.glsl", "fshader00_v150.glsl"))!=-1);
	glUseProgram(program);  //make it the active one

	//get the location of the vPosition attribute
	assert((vPosition = glGetAttribLocation(program, "vPosition")) != -1);
	glEnableVertexAttribArray(vPosition);  //enable it
	//associate the area in the active VBO with this attribute and tell it how data to pull out for each vertex from the VBO
	//glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	assert((vColor = glGetAttribLocation(program, "vColor")) != -1);
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)8);
	//get the location of the uniform color in the shader
	//assert((vColor = glGetUniformLocation(program, "color"))!=-1);
}

vec4 Circle::randColor(){
	float r = ((float) rand() / (RAND_MAX));
	float g = ((float) rand() / (RAND_MAX));
	float b = ((float) rand() / (RAND_MAX));
	return vec4(r,g,b,1.0);
}

void Circle::draw(Camera cam, vector<Light> lights){
	//make this object's VAO active
	//this in turn makes it's associate VBO active
	//and the attributes links to the shader
	glBindVertexArray(VAO); 
	glUseProgram(program);  //also switch to using this shader program

	//unfortunately, every time we draw we still need to set again all uniform variables
	//vec4 rgba = vec4(0.0, 0.0, 1.0, 1.0);// RGBA colors
	//glUniform4fv(vColor, 1, vRgba);

	//now that we're all set up, the the GPU to render NumVertice vertexes as a triangle fan
	//starting at offset 0 in the VBO
	glDrawArrays(GL_TRIANGLE_FAN, 0, NumVertices);

}
