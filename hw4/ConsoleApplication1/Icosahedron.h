#ifndef __ICOSAHEDRON_H__
#define __ICOSAHEDRON_H__

#include "Angel.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include <string>
#include <vector>

using namespace std;

class Icosahedron: public Drawable{


public:
	Icosahedron();
	~Icosahedron();
	void draw(Camera, vector<Light>);
	void drawLines();
	vec4 randColor();

private:
	void buildIcosahedron();
	void makeQuad(int, int, int, int);
	void makeQuad(int ind1, int ind2, int ind3, int ind4, vec4 color);
    void makeTri(int ind1, int ind2, int ind3);
	GLuint vPosition;
	GLuint vColor;
	GLuint mmLoc;
	GLuint viewLoc;
	GLuint projLoc;

	unsigned int index;

	vec4 vertices[12];
	//vec4 potentialColors[12];

	vec4 points[10 * 2 * 3]; //6 faces, 2 triangles/face, 3 vertices per triangle
	vec4 colors[10 * 2 * 3];
};
#endif
