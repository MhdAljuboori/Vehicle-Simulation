#pragma once

#include <stdio.h>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

class SkyBox
{
public:
	SkyBox(int &texture_num, char *filenameBack, char *filenameFront, char *filenameTop, 
			char *filenameDown, char *filenameRight, char *filenameLeft);
	~SkyBox(void);

	void Draw();
private:
	int num_texture;

	int index; 
	int textureID;
	int top, down, right, left, front, back;
	int LoadTexture(char *filename,int alpha=255);

	void DrawFace();
	void DrawCube(float xPos   , float yPos   ,  float zPos , // location pf my cube
  			  float xSize  , float ySize  ,  float zSize , // dimensions of my cube
			  float xRot   , float yRot   ,  float zRot , // rotation angles
			  float R , float G , float B ,// color of my cube
			  GLenum mode);   // polygon mode of my cube
};

