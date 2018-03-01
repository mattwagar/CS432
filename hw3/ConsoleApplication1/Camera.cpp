#include "Camera.h"
#define PI 3.14159265


Camera::Camera(){
	projectionType = true; //false == orthographic , true == perspective
	vec4 UP = vec4(1.0f,1.0f,1.0f,1.0f);
	vec4 VPN = vec4(2.5f, 2.5f, 2.0f, 1.0f);
	eye = vec4(2.5f, 2.5f, 2.0f, 1.0f);
	n = VPN / length(VPN);
	u = cross(UP, n) / length(cross(UP, n));
	v = cross(n,u);
	update();
	
};

Camera::Camera(int _w, int _h){
	projectionType = true; //false == orthographic , true == perspective
	vec4 UP = vec4(1.0f,0.0f,0.0f,1.0f);
	vec4 VPN = vec4(2.5f, 2.5f, 2.0f, 1.0f);
	eye = vec4(2.5f, 2.5f, 2.0f, 1.0f);
	n = VPN / length(VPN);
	u = cross(UP, n);
	v = cross(n,u);
	w = _w;
	h = _h;
	update();
}

mat4 Camera::getProjMatrix(){

	float left = -1.0f;
	float right = 1.0f;
	float bottom = -1.0f;
	float top = 1.0f;
	float n = -10.0f;
	float f = 10.0f;


	if(projectionType){ //perspective
		//return Frustum(left, right, bottom, top, n, f);
		return Perspective(65.0f, (float)w/(float)h,  1.0f, 100.0f);
	} else { //orthographic
		return Ortho(left, right, bottom, top, n, f);
	}
}

mat4 Camera::getCameraMatrix(){
	return view;
}

void Camera::setProjection(bool type){
	projectionType = type;
}



void Camera::update(){
	v = cross(n,u);
	vec4 at = eye - n;
	vec4 up = v;
	view = LookAt( eye, at, up);
}

void Camera::nInc(float inc){
	cout << "n: " << n << "\n";
	n= mat4(1,0,0,inc,
		   0,1,0,inc,
		   0,0,1,inc,
		   0,0,0,1) * n;
}

void Camera::uInc(float inc){
	cout << "inc: " << inc << "\n";
	//cout << "u: " << u << "\n";
	cout << "eye: " << eye << "\n";


	//vec3 orth = inc*cross(u,-n);
	eye = Translate(u*inc)*eye;
}
void Camera::yaw(float deg){
	float rad = deg*PI/180;
	n = n;
	u = cos(rad)*u - sin(rad)*v;
	v = sin(rad)*u + cos(rad)*v;
}

void Camera::pitch(float deg){
	float rad = deg*PI/180;
	u = u;
	v = cos(rad)*v - sin(rad)*n;
	n = sin(rad)*v + cos(rad)*n;
}

void Camera::roll(float deg){
	float rad = deg*PI/180;
	v = v;
	n = cos(rad)*n - sin(rad)*u;
	u = sin(rad)*n + cos(rad)*u;
}