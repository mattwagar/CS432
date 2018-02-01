#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Angel.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include "Vertex.h"
#include <string>
#include <vector>

using namespace std;

class Triangle: public Drawable{


public:	
	Triangle();
	Triangle(vec4 _rgba);
	Triangle(vec4 _rgba, vec3 pos1, vec3 pos2, vec3 pos3);
	~Triangle();
	void init();
	void draw(Camera, vector<Light>);
	void rotate();
	
private:
	static const int NumVertices = 3;
	unsigned int theta;
	vector<Vertex> vertices;
	vec3 pos1; 
	vec3 pos2; 
	vec3 pos3; 
	vec4 vRgba;
	GLuint vPosition;
	GLuint vColor;
};
#endif
