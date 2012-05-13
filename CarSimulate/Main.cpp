
#include <windows.h>		// Header File For Windows
#include <gl/GL.h>				// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <gl/glut.h>			// Header File For The GLut32 Library
#include <fstream>
#include <math.h>
#include "main.h"
#include "Texture.h"
#include "camera.h"
#include "Model_3DS.h"
#include "Environment.h"
#include "Light.h"
//include lib file

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glut32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"GLAUX.LIB")

using namespace std;

HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE; 	// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
//******************************************
// ============= Members Definition =========

//==========================================
int texture_num;
bool CClicked = FALSE;

Camera *myCamera;
Terrain* terrain;
SkyBox* skyBox;

Texture blackTexture;
Texture woodTexture;
Texture woodTexture1;
Texture road;
Texture buildingTexture;
Texture buildingTexture1;

Model_3DS* tank;
GLTexture body;
GLTexture MGunM;
GLTexture MGun;

bool gp; // G Pressed?
GLuint filter; // Which Filter To Use
GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR }; // Storage For Three Types Of Fog
GLuint fogfilter= 2; // Which Fog To Use
GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f}; // Fog Color

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,10000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}
GLUquadric *quadric ;

GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.0f, 1.0f };
GLfloat LightDiffuse[]=		{ 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat LightSpecular[] =   { 1.0, 1.0, 1.0, 1.0 };
GLfloat LightPosition[]=	{ 0.0f, 200.0f, 0.0f, 1.0f };

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations	
	quadric = gluNewQuadric();
	
	glClearColor(0.5f,0.5f,0.5f,1.0f); // We'll Clear To The Color Of The Fog
	glFogi(GL_FOG_MODE, fogMode[fogfilter]); // Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor); // Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.35f); // How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE); // Fog Hint Value
	glFogf(GL_FOG_START, 1.0f); // Fog Start Depth
	glFogf(GL_FOG_END, 1000.0f); // Fog End Depth
	glEnable(GL_FOG);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT,  LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);		// Position The Light

	// Initialize camera
	myCamera = new Camera(Vector3D(100, 300, 300), Vector3D(0, 0, -1));

	// Terrain
	terrain = new Terrain(keys, texture_num);
	// Terrain Texture
	terrain->LoadTexture("Data/terrain ground.bmp");
	// Load Heightmap
	terrain->LoadHeightMap("Data/terrain height.bmp");
	// Draw Terrain
	terrain->Draw(0,-71,0);


	// Tank
	tank = new Model_3DS();
	// Load Model
	tank->Load("Data/Models/FinalTank.3ds");
	// Load Tank textures
	body.LoadBMP("Data/tanktexture/teext.bmp");
	MGunM.LoadBMP("Data/tanktexture/GunM.bmp");
	MGun.LoadBMP("Data/tanktexture/MGun.bmp");

	// Skybox with load texture
	skyBox = new SkyBox("data/skybox/top.bmp", "data/skybox/down.bmp", "data/skybox/left.bmp", 
					"data/skybox/right.bmp", "data/skybox/front.bmp", "data/skybox/back.bmp");

	blackTexture.loadTexture("data/black.bmp");
	woodTexture.loadTexture("data/wood.bmp");
	woodTexture1.loadTexture("data/wood1.bmp");
	road.loadTexture("data/road.bmp");
	buildingTexture.loadTexture("data/Building.bmp");
	buildingTexture1.loadTexture("data/Building1.bmp");

	glColor4f(1.0f, 1.0f, 1.0f, 0.5);					// Full Brightness.  50% Alpha
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency

	return true;										// Initialization Went OK
}

void DrawGlass(float width = 10, float height=5, float posX=0, float posY=0, float posZ=0, 
				float angle=45, float rotX=1, float rotY=0, float rotZ=0)
{
	glPushMatrix();
		glTranslatef(posX, posY, posZ);
		if (rotY > 0)
			glRotatef(rotY-15, 0, 1, 0);
		if (rotY < 0)
			glRotatef(rotY+15, 0, 1, 0);
		glRotatef(angle, rotX, rotY, rotZ);
		glEnable(GL_BLEND);			// Turn Blending On
		glBegin(GL_QUADS);
		glColor3f(0, 0, 0.3);
		glVertex3f(width, height, 0);
		glVertex3f(width, -height, 0);
		glVertex3f(-width, -height, 0);
		glVertex3f(-width, height, 0);
		glEnd();
		glDisable(GL_BLEND);			// Turn Blending Off
	glPopMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 0.5);
}

void DrawCube(float width, float height, float length, 
				float posX=0, float posY=0, float posZ=0, 
				float angle=0, float rotX=0, float rotY=0, float rotZ=0, 
				int frontTex=-1, int backTex=-1, int rightTex=-1, int leftTex=-1, 
				int upTex=-1, int downTex=-1)
{
	glPushMatrix();
	
	glTranslatef(posX, posY, posZ);
	glRotatef(angle, rotX, rotY, rotZ);
	
	if (frontTex != -1)
		glBindTexture(GL_TEXTURE_2D, frontTex);
	glBegin(GL_QUADS);
		//front
		glNormal3f(0, 0, 1);
		if (frontTex != -1)
			glTexCoord2f(1, 0);
		glVertex3f(width,-height,length);
		if (frontTex != -1)
			glTexCoord2f(1, 1);
		glVertex3f(width,height,length);
		if (frontTex != -1)
			glTexCoord2f(0, 1);
		glVertex3f(-width,height,length);
		if (frontTex != -1)
			glTexCoord2f(0, 0);
		glVertex3f(-width,-height,length);
	glEnd();
	
	if (backTex != -1)
		glBindTexture(GL_TEXTURE_2D, backTex);
	glBegin(GL_QUADS);
		//back
		glNormal3f(0, 0, -1);
		if (backTex != -1)
			glTexCoord2f(1, 0);
		glVertex3f(width,-height,-length);
		if (backTex != -1)
			glTexCoord2f(1, 1);
		glVertex3f(width,height,-length);
		if (backTex != -1)
			glTexCoord2f(0, 1);
		glVertex3f(-width,height,-length);
		if (backTex != -1)
			glTexCoord2f(0, 0);
		glVertex3f(-width,-height,-length);
	glEnd();

	if (rightTex != -1)
		glBindTexture(GL_TEXTURE_2D, rightTex);
	glBegin(GL_QUADS);
		//right
		glNormal3f(1, 0, 0);
		if (rightTex != -1)
			glTexCoord2f(1, 0);
		glVertex3f(width,-height,-length);
		if (rightTex != -1)
			glTexCoord2f(1, 1);
		glVertex3f(width,height,-length);
		if (rightTex != -1)
			glTexCoord2f(0, 1);
		glVertex3f(width,height,length);
		if (rightTex != -1)
			glTexCoord2f(0, 0);
		glVertex3f(width,-height,length);
	glEnd();

	if (leftTex != -1)
		glBindTexture(GL_TEXTURE_2D, leftTex);
	glBegin(GL_QUADS);
		//left
		glNormal3f(-1, 0, 0);
		if (leftTex != -1)
			glTexCoord2f(1, 0);
		glVertex3f(-width,-height,length);
		if (leftTex != -1)
			glTexCoord2f(1, 1);
		glVertex3f(-width,height,length);
		if (leftTex != -1)
			glTexCoord2f(0, 1);
		glVertex3f(-width,height,-length);
		if (leftTex != -1)
			glTexCoord2f(0, 0);
		glVertex3f(-width,-height,-length);
	glEnd();

	if (upTex != -1)
		glBindTexture(GL_TEXTURE_2D, upTex);
	glBegin(GL_QUADS);
		//up
		glNormal3f(0, 1, 0);
		if (upTex != -1)
			glTexCoord2f(1, 0);
		glVertex3f(width,height,length);
		if (upTex != -1)
			glTexCoord2f(1, 1);
		glVertex3f(width,height,-length);
		if (upTex != -1)
			glTexCoord2f(0, 1);
		glVertex3f(-width,height,-length);
		if (upTex != -1)
			glTexCoord2f(0, 0);
		glVertex3f(-width,height,length);
	glEnd();

	if (downTex != -1)
		glBindTexture(GL_TEXTURE_2D, downTex);
	glBegin(GL_QUADS);
		//down
		glNormal3f(0, -1, 0);
		if (downTex != -1)
			glTexCoord2f(1, 0);
		glVertex3f(width,-height,-length);
		if (downTex != -1)
			glTexCoord2f(1, 1);
		glVertex3f(width,-height,length);
		if (downTex != -1)
			glTexCoord2f(0, 1);
		glVertex3f(-width,-height,length);
		if (downTex != -1)
			glTexCoord2f(0, 0);
		glVertex3f(-width,-height,-length);
	glEnd();
	glPopMatrix();
}

void DrawFace(float width, float height, float length, 
				float posX=0, float posY=0, float posZ=0, 
				float angle=0, float rotX=0, float rotY=0, float rotZ=0, int texture=-1)
{
	glPushMatrix();
	glTranslatef(posX, posY, posZ);
	glRotatef(angle, rotX, rotY, rotZ);
	if (texture != -1)
		glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		if (texture != -1)
			glTexCoord2f(1, 0);
		glVertex3f(width,0,length);
		if (texture != -1)
			glTexCoord2f(1, 1);
		glVertex3f(width,0,length);
		if (texture != -1)
			glTexCoord2f(0, 1);
		glVertex3f(-width,0,length);
		if (texture != -1)
			glTexCoord2f(0, 0);
		glVertex3f(-width,0,length);
	glEnd();
	glPopMatrix();
}

float toRadian(float d)
{
	return (3.14*tank->rot.y)/180;
}

void DrawTower(float posX, float posY, float posZ)
{
	//300, 180, 40
	DrawCube(4, 50, 4, posX-20, posY-80, posZ, 5, 1, 0, 0, woodTexture1.getTexture(), woodTexture1.getTexture(), 
		woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture());
	DrawCube(4, 50, 4, posX-20, posY-80, posZ-40, -5, 1, 0, 0, woodTexture1.getTexture(), woodTexture1.getTexture(), 
		woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture());

	DrawCube(2, 50, 2, posX-20, posY-80, posZ-20, 28, 1, 0, 0, woodTexture1.getTexture(), woodTexture1.getTexture(), 
		woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture());
	DrawCube(2, 50, 2, posX-20, posY-80, posZ-20, -28, 1, 0, 0, woodTexture1.getTexture(), woodTexture1.getTexture(), 
		woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture());

	DrawCube(4, 50, 4, posX+20, posY-80, posZ-40, -5, 1, 0, 0, woodTexture1.getTexture(), woodTexture1.getTexture(), 
		woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture());
	DrawCube(4, 50, 4, posX+20, posY-80, posZ, 5, 1, 0, 0, woodTexture1.getTexture(), woodTexture1.getTexture(), 
		woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture());

	DrawCube(2, 50, 2, posX+20, posY-80, posZ-20, -28, 1, 0, 0, woodTexture1.getTexture(), woodTexture1.getTexture(), 
		woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture());
	DrawCube(2, 50, 2, posX+20, posY-80, posZ-20, 28, 1, 0, 0, woodTexture1.getTexture(), woodTexture1.getTexture(), 
		woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture(), woodTexture1.getTexture());

	DrawCube(30, 35, 30, posX, posY, posZ-20, 0, 0, 0, 0, woodTexture.getTexture(), woodTexture.getTexture(),
			woodTexture.getTexture(), woodTexture.getTexture(), 
			woodTexture.getTexture(), woodTexture.getTexture());
	DrawCube(40, 2, 40, posX, posY+30, posZ-20, 0, 0, 0, 0, woodTexture.getTexture(), woodTexture.getTexture(),
			woodTexture.getTexture(), woodTexture.getTexture(), 
			woodTexture.getTexture(), woodTexture.getTexture());
}

void DrawRoad()
{
	DrawCube(50, 1, 60, 208, -14.7, 647, -70, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 70, 285, -14.9, 590, -40, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 50, 340, -15, 505, -20, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 40, 363, -14.9, 432, -15, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 60, 373, -14.8, 352, -5, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 20, 375, -14.7, 290, 10, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 20, 368, -14.6, 273, 20, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 40, 344, -14.8, 250, 50, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 60, 272, -14.7, 230, 80, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 60, 182, -14.5, 205, 60, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 40, 100, -14.4, 158, 60, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 40, 53, -14.3, 120, 40, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 40, 20, -14.2, 65, 20, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 40, 6, -14.1, 2, 0, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 40, 20, -14.0, -48, -30, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 60, 70, -13.9, -90, -60, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 50, 150, -15.0, -135, -70, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 80, 265, -15.0, -178, -70, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 30, 350, -14.9, -220, -50, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 40, 382, -14.8, -262, -30, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 30, 400, -14.7, -310, -10, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 30, 400, -14.6, -350, 10, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 30, 380, -14.5, -390, 30, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 30, 350, -14.4, -420, 50, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 50, 290, -14.4, -470, 50, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 30, 240, -14.3, -500, 70, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 30, 200, -14.1, -510, 90, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 190, 80, -15, -510, 90, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 150, -260, -15, -510, 90, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 30, -422, -14.9, -505, 110, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 50, -495, -14.9, -480, 110, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 30, -570, -14.9, -452, 110, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 30, -608, -14.8, -430, 130, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 30, -635, -14.7, -400, 150, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 60, -668, -14.6, -345, 150, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 60, -726, -15, -242, 150, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 60, -750, -14.9, -157, 0, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 60, -742, -14.8, -62, 10, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 60, -742, -14.7, -62, 10, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 60, -710, -14.6, 30, 30, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 90, -645, -15, 140, 30, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 50, -576, -14.9, 235, 50, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 50, -500, -15, 300, 50, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 80, -405, -15, 378, 50, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 100, -275, -15, 486, 50, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 30, -185, -14.9, 550, 70, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 80, -95, -15, 582, 70, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 80, 50, -15, 635, 70, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
	DrawCube(50, 1, 30, 140, -14.8, 660, 90, 0, 1, 0, -1, -1, -1, -1, road.getTexture());
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();// Reset The Current Modelview Matrix
	
	if (!CClicked)
	{
		if(keys['A'])
			myCamera->RotateY(0.5);
		if(keys['D'])
			myCamera->RotateY(-0.5);
		if(keys['W'])
			myCamera->MoveForward(2.5);
		if(keys['S'])
			myCamera->MoveForward(-2.5);
		if(keys['X'])
			myCamera->RotateX(0.5);	
		if(keys['Z'])
			myCamera->RotateX(-0.5);
		if(keys['F'])
			myCamera->Move(Vector3D(0,-4,0));
		if(keys['R'])
			myCamera->Move(Vector3D(0,4,0));
	}
	myCamera->Render();

	if(keys[VK_LEFT])
	{
		tank->rot.y += 1;
		if (CClicked)
			myCamera->RotateY(1);
	}
	else if(keys[VK_RIGHT])
	{
		tank->rot.y -= 1;
		if (CClicked)
			myCamera->RotateY(-1);
	}
	else if(keys[VK_UP])
	{
		float r = toRadian(tank->rot.y);
		tank->pos.x -= 2*sin(r);
		tank->pos.z -= 2*cos(r);
	}
	else if(keys[VK_DOWN])
	{
		float r = toRadian(tank->rot.y);
		tank->pos.x += 2*sin(r);
		tank->pos.z += 2*cos(r);
	}
	
	terrain->draw();
	DrawCube(80, 80, 80, 0, 65, -750, 0, 0, 0, 0, buildingTexture.getTexture());
	DrawCube(80, 100, 80, -300, 85, -750, 0, 0, 0, 0, buildingTexture1.getTexture());

	DrawTower(300, 180, 40);

	DrawTower(-280, 220, 200);
	
	DrawRoad();

	skyBox->draw();

	Model_3DS::Color ambient;
	ambient.a = 1;
	ambient.b = 0.5;
	ambient.g = 0.5;
	ambient.r = 0.5;
	tank->Materials[0].ambient = ambient;

	Model_3DS::Color diffuse;
	diffuse.a = 1;
	diffuse.b = 1;
	diffuse.g = 1;
	diffuse.r = 1;
	tank->Materials[0].diffuse = diffuse;

    tank->Draw();
	tank->Materials[0].tex = body;
	tank->Materials[3].tex = MGun;
	tank->Materials[4].tex = MGunM;
	tank->Materials[5].tex = MGun;

	if (CClicked)
	{
		myCamera->Position.setVector3D(tank->pos.x, tank->pos.y+20, tank->pos.z);
		
		Vector3D camPos  = myCamera->getPosition();
		Vector3D camRot  = myCamera->getRotation();
		Vector3D camView = myCamera->getView();
		DrawGlass(10, 5, camPos.getX()+ (camView.getX()*5), camPos.getY() + (camView.getY()*5), 
				camPos.getZ() + (camView.getZ()*5), 30, 
				camRot.getX(), camRot.getY(), camRot.getZ());
	}

	return true;
} 

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam){
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	fullscreen=FALSE;							// Windowed Mode

	// Create Our OpenGL Window
	if (!CreateGLWindow("Veiche Simulation",700,500,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)								// Program Active?
			{
				if (keys[VK_ESCAPE])				// Was ESC Pressed?
				{
					done=TRUE;						// ESC Signalled A Quit
				}
				else								// Not Time To Quit, Update Screen
				{
					DrawGLScene();					// Draw The Scene
					SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
				}
			}
			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("Mhd Aljobory && Qusay Kamel && Mhd Jarrah (Car Simulation)",700,500,16,fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
			if (keys['C'] && !CClicked)
			{
				CClicked = TRUE;
				myCamera->Reset();
				myCamera->RotateY(tank->rot.y);
			}
			else if (keys['V'] && CClicked)
			{
				CClicked = FALSE;
				myCamera->Position.setY(myCamera->Position.getY()+100);
				myCamera->View.setY(-2);
			}
			if (keys['G'])
			{
				glEnable(GL_FOG);		// Enables GL_FOG
				glDisable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
			}
			else if (keys['L'])
			{
				glDisable(GL_FOG);		// Disable GL_FOG
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
			}
			else if (keys['O'])
			{
				glDisable(GL_FOG);
				glDisable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}