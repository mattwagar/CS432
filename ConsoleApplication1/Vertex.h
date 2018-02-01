#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "Angel.h"

class Vertex{


public:	
	Vertex();
	Vertex(vec3 _position, vec4 _color);
	vec3 position;
	vec4 color;
	
	
};

#endif