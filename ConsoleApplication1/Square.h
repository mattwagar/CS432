#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Angel.h"
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
	Square(vec4 _rgba, vec2 pos1, vec2 pos2, vec2 pos3, vec2 pos4);
	~Square();
	void init();
	void init(vec2 pos1, vec2 pos2, vec2 pos3, vec2 pos4);
	void draw(Camera, vector<Light>);
	
private:
	static const int NumVertices = 4;
	vec4 vRgba;
	GLuint vPosition;
	GLuint vColor;
};
#endif
