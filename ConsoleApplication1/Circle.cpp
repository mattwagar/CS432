#include "Circle.h"
#define PI 3.14159265


Circle::Circle() {
	vRgba = vec4(0.0, 1.0, 0.0, 1.0);
	NumVertices = 12;
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
	//vec2 *points = new vec2[NumVertices];

	vector<vec2> points(NumVertices);

	points[0] = vec2(0, 0); 
	float angle = NumVertices-1 == 0 ? 360 : 360 / (NumVertices-1);
	cout << "\nangle: " << angle << "\n";
	for(int i = 1; i < NumVertices; i++){

		float x = cos((i-1) *  angle  *PI/180);
		float y = sin((i-1) *  angle  *PI/180);

		x = abs(x) <= 1e-004 ? 0 : x; 
		y = abs(y) <= 1e-004 ? 0 : y; 
		
		points[i] = vec2(x,y);
		cout <<		vec2(x,y) << "\n";
	}
	points.push_back(points[1]);
	NumVertices++;


	//put the data on the VBO
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(points), &points[0], GL_STATIC_DRAW);
	
	//Now let's set up the shaders!!
	// Load shaders
	assert((program = InitShader("vshader00_v150.glsl", "fshader00_v150.glsl"))!=-1);
	glUseProgram(program);  //make it the active one

	//get the location of the vPosition attribute
	assert((vPosition = glGetAttribLocation(program, "vPosition")) != -1);
	glEnableVertexAttribArray(vPosition);  //enable it
	//associate the area in the active VBO with this attribute and tell it how data to pull out for each vertex from the VBO
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	//get the location of the uniform color in the shader
	assert((vColor = glGetUniformLocation(program, "color"))!=-1);
}

void Circle::draw(Camera cam, vector<Light> lights){
	//make this object's VAO active
	//this in turn makes it's associate VBO active
	//and the attributes links to the shader
	glBindVertexArray(VAO); 
	glUseProgram(program);  //also switch to using this shader program

	//unfortunately, every time we draw we still need to set again all uniform variables
	//vec4 rgba = vec4(0.0, 0.0, 1.0, 1.0);// RGBA colors
	glUniform4fv(vColor, 1, vRgba);

	//now that we're all set up, the the GPU to render NumVertice vertexes as a triangle fan
	//starting at offset 0 in the VBO
	glDrawArrays(GL_TRIANGLE_FAN, 0, NumVertices);

}
