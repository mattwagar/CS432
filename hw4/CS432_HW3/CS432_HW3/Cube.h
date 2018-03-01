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

private:
	void buildCube();
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
