#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "Angel.h"

using namespace std;

class Camera {
	public:
		Camera();
		Camera(int _w, int _h);
		mat4 getProjMatrix();
		mat4 getCameraMatrix();
		void update();
		void setProjection(bool type);
		void nInc(float inc);
		void uInc(float inc);
		void yaw(float deg);
		void pitch(float deg);
		void roll(float deg);
		void setEye(vec4 mm, vec4 _n) { eye = mm; n = _n; }


	private:
		bool projectionType;
		int w;
		int h;
		mat4 view;
		vec4 eye;
		vec4 u;
		vec4 v;
		vec4 n;
};

#endif
