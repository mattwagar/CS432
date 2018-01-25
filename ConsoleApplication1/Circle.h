#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "Angel.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include "Vertex.h"
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class Circle: public Drawable{


public:	
	Circle();
	Circle(vec4 _rgba);
	~Circle();
	void init();
	vec4 randColor();
	void draw(Camera, vector<Light>);
	
private:
	int NumVertices;
	vec4 vRgba;
	GLuint vPosition;
	GLuint vColor;
};
#endif
