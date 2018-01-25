#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "Angel.h"

class Vertex{


public:	
	Vertex();
	Vertex(vec2 _position, vec4 _color);

private:	
	vec2 position;
	vec4 color;
	
};

#endif