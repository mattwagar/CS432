#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Angel.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include <string>
#include <vector>

using namespace std;

class Square: public Drawable{


public:	
	Square();
	Square(vec4 _rgba);
	~Square();
	void init();
	void draw(Camera, vector<Light>);
	
private:
	static const int NumVertices = 4;
	vec4 vRgba;
	GLuint vPosition;
	GLuint vColor;
};
#endif
