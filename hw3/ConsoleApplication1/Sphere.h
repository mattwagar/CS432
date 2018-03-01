#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Angel.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include <string>
#include <vector>

class Sphere :public Drawable {
public:
	Sphere();
	void draw(Camera, vector<Light>);
	~Sphere();
private:
	//(4 triangular faces per tetrahedron)^(numDivisions+1)*3 vertices per triangle
	static const unsigned int numVertices = 3072;
	void build();
	GLuint vPosition, vColor; //locations of attributes
	GLuint program, mmLoc, viewLoc, projLoc; //locations of uniforms
								//data
	vec4 vertexLocations[numVertices];
	vec4 vertexColors[numVertices];
	//helper stuff
	unsigned int index;
	float sqrt2, sqrt6;
	void tetrahedron(int);
	void divideTriangle(const vec4&, const vec4&, const vec4&, int);
	void triangle(const vec4&, const vec4&, const vec4&);
	vec4 unit(const vec4&);
};

#endif