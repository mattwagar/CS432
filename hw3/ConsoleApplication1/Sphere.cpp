#include "Sphere.h"
#define PI 3.14159265

Sphere::Sphere() {

	modelmatrix = mat4();
	
	build();

	assert((program = InitShader("vshader00_v150.glsl", "fshader00_v150.glsl")) != -1);
	//assert((mmLoc = glGetUniformLocation(program, "model_matrix")) != -1);
	//assert((viewLoc = glGetUniformLocation(program, "view_matrix")) != -1);
	//assert((projLoc = glGetUniformLocation(program, "proj_matrix")) != -1);
}

Sphere::~Sphere() {

}


void Sphere::build() {
	
	sqrt2 = (float)sqrt(2.0);
	sqrt6 = (float)sqrt(6.0);

	index = 0;

	tetrahedron(4);

	

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexColors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations), sizeof(vertexColors), vertexColors);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); //make this VAO active
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //associate the VBO with the active VAO

	assert((program = InitShader("vshader00_v150.glsl", "fshader00_v150.glsl")) != -1);
	glUseProgram(program);  //make it the active one

	assert((vPosition = glGetAttribLocation(program, "vPosition")) != -1);
	glEnableVertexAttribArray(vPosition);  //enable it
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	//get the location of the uniform color in the shader
	assert((vColor = glGetAttribLocation(program, "vColor")) != -1);
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations)));

	//get the location of the model matrix
	assert((mmLoc = glGetUniformLocation(program, "model_matrix")) != -1);
	assert((viewLoc = glGetUniformLocation(program, "view_matrix")) != -1);
	assert((projLoc = glGetUniformLocation(program, "proj_matrix")) != -1);

}

void Sphere :: tetrahedron(int count) {
	vec4 v[4] = {
		vec4(0,0,1,1),
		vec4(0,2 * sqrt2 / 3, -1.0f / 3.0f,1),
		vec4(-sqrt6 / 3.0f, -sqrt2 / 3.0f, -1.0f / 3.0f, 1.0f),
		vec4(sqrt6 / 3.0f, -sqrt2 / 3.0f, -1.0f / 3.0f, 1.0f),
	};

	divideTriangle(v[0], v[1], v[2], count);
	divideTriangle(v[3], v[2], v[1], count);
	divideTriangle(v[0], v[3], v[1], count);
	divideTriangle(v[0], v[2], v[3], count);
}

void Sphere::triangle(const vec4& a,const vec4& b,const vec4& c) {
	//triangle #1

	vec4 color((float)1.0*rand() / RAND_MAX,    (float)1.0*rand() / RAND_MAX,   (float)1.0*rand() / RAND_MAX, (float)1.0);

	vertexLocations[index] = a;
	vertexColors[index] = color;
	index++;

	vertexLocations[index] = b;
	vertexColors[index] = color;
	index++;

	vertexLocations[index] = c;
	vertexColors[index] = color;
	index++;
}

void Sphere::divideTriangle(const vec4& a, const vec4& b, const vec4& c, int count) {
	if (count > 0) {
		vec4 v1 = unit(a + b);
		v1.w = 1.0;
		vec4 v2 = unit(a + c);
		v2.w = 1.0;
		vec4 v3 = unit(b + c);
		v1.w = 1.0;
	
		divideTriangle(a, v1, v2, count - 1);
		divideTriangle(c, v2, v3, count - 1);
		divideTriangle(b, v3, v1, count - 1);
		divideTriangle(v1, v3, v2, count - 1);
	}
	else {
		triangle(a, b, c);
	}
}

vec4 Sphere::unit(const vec4& p) {
	float len = p.x*p.x + p.y*p.y + p.z*p.z;
	vec4 t;
	if (len > DivideByZeroTolerance) {
		t = p / sqrt(len);
		t.w = 1.0;
	}
	return t;
}

void Sphere::draw(Camera cam, vector<Light> lights) {

	glBindVertexArray(VAO);
	glUseProgram(program);  //also switch to using this shader program
	glUniformMatrix4fv(mmLoc, 1, GL_TRUE, modelmatrix);
	glUniformMatrix4fv(viewLoc, 1, GL_TRUE, cam.getCameraMatrix());
	glUniformMatrix4fv(projLoc, 1, GL_TRUE, cam.getProjMatrix());
	glDrawArrays(GL_TRIANGLES, 0, 3072);


}

void circleFace() {}