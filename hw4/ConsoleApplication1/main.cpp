//
// A GLSL "Hello World"
// Display a blue square
//

#include "Angel.h"  //includes gl.h, glut.h and other stuff...
#include "Camera.h"  //for camera objects (for use in future assignments)
#include "Light.h"	//for lights (for use in future assignments)
#include "Camera.h"
//#include "Cube.h"  //blue box object!
//#include "Polyhedron.h"  //blue box object!
//#include "Icosahedron.h"
#include "Sphere.h"

//Forward declarations
void init(void);
void display(void);
void keyboard(unsigned char, int, int);
void keyboardup(unsigned char, int, int);
void specialInput(int key, int x, int y);
void specialInputUp(int key, int x, int y);

void resize(int width, int height);
void close(void);
void timerCallback(int value);

bool camToggle;

bool animateX = false;
bool animateY = false;
bool animateZ = false;
bool animateNegX = false;
bool animateNegY = false;
bool animateNegZ = false;
bool Up = false;
bool Down = false;
bool Left = false;
bool Right = false;
bool yaw = false;
bool pitch = false;
bool roll = false;
bool syaw = false;
bool spitch = false;
bool sroll = false;

float rotX = 0;
float rotY = 0;
float rotZ = 0;

//Objects
//Cube* mbox;
//Polyhedron* mpoly;
//Icosahedron* micos;
Sphere* msphere;
Camera* cam;
Camera cam1;
Camera cam2;
vector<Light> lights;
vector<Drawable*>drawables;
int width = 500;
int height = 500;

GLuint windowID=0;
//----------------------------------------------------------------------------

int main(int argc, char **argv)
{
	//initialize GLUT
	glutInit(&argc, argv);
#ifdef __APPLE__
	glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_SINGLE);
#else
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
#endif
	glutInitWindowSize(500, 500);

	windowID = glutCreateWindow("3D Sample");

	//print out info about our system
	fprintf(stdout, "OpenGL Version: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	//initialize glew on non-apple systems
#ifndef __APPLE__
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif

	init(); //initalize objects

	//set up the callback functions
	glutDisplayFunc(display);
	glutWMCloseFunc(close);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);
	glutSpecialFunc(specialInput);
	glutSpecialUpFunc(specialInputUp);
	glutTimerFunc(30, timerCallback, 0);

	//start the main event listening loop
	glutMainLoop();

	return 0;
}

// Initialization
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	//mbox = new Cube();
	//mbox->setModelMatrix(RotateX(-60)*RotateY(10));

	//mpoly = new Polyhedron();
	//mpoly->setModelMatrix(RotateX(10)*RotateY(10));

	//micos = new Icosahedron();
	msphere = new Sphere();

	msphere->setModelMatrix(Translate(0,1,-4));
	
	//drawables.push_back(mbox);
	//drawables.push_back(micos);
	//drawables.push_back(mpoly);
	drawables.push_back(msphere);


	cam1 = Camera(width, height);
	cam1.setEye(vec4(0,2,0,1), vec4(0,0,90,1));
	cam2 = Camera(width, height);
	cam2.setEye(vec4(0, 10, 0, 1), vec4(0, 90, 45, 1));
	cam = & cam1;
	camToggle = false;

}

//----------------------------------------------------------------------------
//Display callback
void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );



	for (unsigned int i = 0; i < drawables.size(); i++)
		drawables[i]->draw(Camera(*cam), lights);
	glutSwapBuffers();
}

//----------------------------------------------------------------------------
//Window resize callback
void resize(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);  //make the viewport the entire window
}

//----------------------------------------------------------------------------
//Keyboard event callback
void keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
	case 033:  // Escape key
	case 'q': case 'Q':
		close();
	    break;
	case ' ':
		camToggle ? cam = & cam1 : cam = & cam2;
		camToggle = !camToggle;
		break;
	case 'j':
		animateX = true;
		break;
	case 'k':
		animateY = true;
		break;
	case 'l':
		animateZ = true;
		break;
	case 'u':
		animateNegX = true;
		break;
	case 'i':
		animateNegY = true;
		break;
	case 'o':
		animateNegZ = true;
		break;
	case 'z':
		yaw = true;
		break;
	case 'a': case 'Z':
		syaw = true;
		break;
	case 'x':
		pitch = true;
		break;
	case 's': case 'X':
		spitch = true;
		break;
	case 'c':
		roll = true;
		break;
	case 'd': case 'C':
		sroll = true;
		break;
	case 'p':
		cam->setProjection(false);
		break;
	case 'P':
		cam->setProjection(true);
		break;
    }
}
void keyboardup( unsigned char key, int x, int y )
{
    switch( key ) {
	case 033:  // Escape key
	case 'j':
		animateX = false;
		break;
	case 'k':
		animateY = false;
		break;
	case 'l':
		animateZ = false;
		break;
	case 'u':
		animateNegX = false;
		break;
	case 'i':
		animateNegY = false;
		break;
	case 'o':
		animateNegZ = false;
		break;
	case 'z':
		yaw = false;
		break;
	case 'a': case 'Z':
		syaw = false;
		break;
	case 'x':
		pitch = false;
		break;
	case 's': case 'S':
		spitch = false;
		break;
	case 'c':
		roll = false;
		break;
	case 'd': case 'C':
		sroll = false;
		break;
	}
}

void specialInput(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			Up = true;
		break;	
		case GLUT_KEY_DOWN:
			Down = true;
		break;
		case GLUT_KEY_LEFT:
			Left = true;
		break;
		case GLUT_KEY_RIGHT:
			Right = true;
		break;
		//case GLUT_KEY_SHIFT_L:
		//	Shift = true;
		//break;
	}
}

void specialInputUp(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			Up = false;
		break;	
		case GLUT_KEY_DOWN:
			Down = false;
		break;
		case GLUT_KEY_LEFT:
			Left = false;
		break;
		case GLUT_KEY_RIGHT:
			Right = false;
		break;
		//case GLUT_KEY_SHIFT_L:
		//	Shift = false;
		//break;
	}
}

void timerCallback(int value)
{   
	
	if(animateX){
		rotX+=3;
		for (unsigned int i = 0; i < drawables.size(); i++){
			drawables[i]->setModelMatrix(RotateY(rotY) * RotateX(rotX) * RotateZ(rotZ) * drawables[i]->getModelMatrix());
		}	
	}
	if(animateY){
		rotY+=3;
		for (unsigned int i = 0; i < drawables.size(); i++){
			drawables[i]->setModelMatrix(RotateY(rotY) * RotateX(rotX) * RotateZ(rotZ) * drawables[i]->getModelMatrix());
		}	
	}
	if(animateZ){
		rotZ+=3;
		for (unsigned int i = 0; i < drawables.size(); i++){
			drawables[i]->setModelMatrix(RotateY(rotY) * RotateX(rotX) * RotateZ(rotZ) * drawables[i]->getModelMatrix());
		}	
	}

	if(animateNegX){
		rotX-=3;
		for (unsigned int i = 0; i < drawables.size(); i++){
			drawables[i]->setModelMatrix(RotateY(rotY) * RotateX(rotX) * RotateZ(rotZ) * drawables[i]->getModelMatrix());
		}	
	}
	if(animateNegY){
		rotY-=3;
		for (unsigned int i = 0; i < drawables.size(); i++){
			drawables[i]->setModelMatrix(RotateY(rotY) * RotateX(rotX) * RotateZ(rotZ) * drawables[i]->getModelMatrix());
		}	
	}
	if(animateNegZ){
		rotZ-=3;
		for (unsigned int i = 0; i < drawables.size(); i++){
			drawables[i]->setModelMatrix(RotateY(rotY) * RotateX(rotX) * RotateZ(rotZ) * drawables[i]->getModelMatrix());
		}	
	}
	if(Up) cam->nInc(0.05f);
	if(Down) cam->nInc(-0.05f);
	if(Left) cam->uInc(-0.1f);
	if(Right) cam->uInc(0.1f);

	if(syaw)cam->yaw(1.5);
	else if(yaw)cam->yaw(-1.5);
	
	if(spitch)cam->pitch(-1.5);
	else if(pitch)cam->pitch(1.5);
	
	if(sroll)cam->roll(1.5);
	else if(roll)cam->roll(-1.5);

	cam->update();
	
	glutTimerFunc(30, timerCallback, value);
	glutPostRedisplay();
}

void close(){
	for (unsigned int i = 0; i < drawables.size(); i++)
		delete(drawables[i]);

	if(windowID>0)
			glutDestroyWindow(windowID);

    exit(EXIT_SUCCESS);
}