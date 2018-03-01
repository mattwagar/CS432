#ifndef __CUBE_H__
#define __CUBE_H__

#include "Angel.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include <string>
#include <vector>

using namespace std;

class Cube: public Drawable{


public:
	Cube();
	~Cube();
	void draw(Camera, vector<Light>);
	vec4 randColor();

private:
	void buildCube();
	void makeQuad(int, int, int, int);
	void makeQuad(int ind1, int ind2, int ind3, int ind4, vec4 color);
	GLuint vPosition;
	GLuint vColor;
	GLuint mmLoc;

	unsigned int index;

	vec4 vertices[12];
	//vec4 potentialColors[12];

	vec4 points[10 * 2 * 3]; //6 faces, 2 triangles/face, 3 vertices per triangle
	vec4 colors[10 * 2 * 3];
};
#endif
