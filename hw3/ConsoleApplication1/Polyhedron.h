#ifndef __POLYHEDRON_H__
#define __POLYHEDRON_H__

#include "Angel.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include <string>
#include <vector>

using namespace std;

class Polyhedron: public Drawable{


public:
	Polyhedron();
	~Polyhedron();
	void draw(Camera, vector<Light>);
	vec4 randColor();

private:
	void buildPolyhedron();
	void makeQuad(int, int, int, int);
	GLuint vPosition;
	GLuint vColor;
	GLuint mmLoc;

	unsigned int index;

	vec4 vertices[8];
	vec4 potentialColors[8];

	vec4 points[6 * 2 * 3]; //6 faces, 2 triangles/face, 3 vertices per triangle
	vec4 colors[6 * 2 * 3];
};
#endif
