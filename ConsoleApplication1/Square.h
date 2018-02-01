#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Angel.h"
#include "mat.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include "Vertex.h"
#include <string>
#include <vector>

using namespace std;

class Square: public Drawable{


public:	
	Square();
	Square(vec4 _rgba);
	Square(vec4 _rgba, vec3 _pos1, vec3 _pos2, vec3 _pos3, vec3 _pos4);
	~Square();
	void init();
	void init(vec3 pos1, vec3 pos2, vec3 pos3, vec3 pos4);
	void draw(Camera, vector<Light>);
	void rotate();

private:
	static const int NumVertices = 4;
	unsigned int theta;
	vector<Vertex> vertices;
	vec3 pos1; 
	vec3 pos2; 
	vec3 pos3; 
	vec3 pos4;
	vec4 vRgba;
	GLuint model_matrix;
	GLuint vPosition;
	GLuint vColor;
};
#endif
