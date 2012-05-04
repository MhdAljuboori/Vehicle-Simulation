#pragma once

#include <stdio.h>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <iostream>

class Terrain
{
public:
	Terrain(bool keys, //int posX = 0, int posY = 0, int posZ = 0,
			int mapSize = 512, float stepSize = 1/512.0);//, float heightRatio = 1.5f);
	~Terrain(void);

	//get methods
	int getMapSize();
	float getStepSize();
	//float getHeightRatio();
	BYTE* getG_HeightMap();

	// Loads The .RAW File And Stores It In g_HeightMap
	//void LoadRawFile(LPSTR strName);

	// This Returns The Height From A Height Map Index
	//int Height(int X, int Y);
	// This Sets The Color Value For A Particular Index
	//void SetVertexColor(int x, int y);
	// This Renders The Height Map As Quads
	//void RenderHeightMap();

	void Draw();

	float scaleValue;		// Scale Value For The Terrain

	void setWire();
	void setPolygon();
	void setWireNot();

	bool IsPolygon();
	
	// Loads A Bitmap Image
	//AUX_RGBImageRec* LoadBMP(char *Filename);
	// Load Bitmaps And Convert To Textures
	//int LoadGLTextures();

	void LoadTexture(char *filename,int alpha=255);
	void LoadHeightMap(char *filename);

	inline GLubyte GetValue(int i ,int j  )  
		{return (int)(HeightMap[i*mapSize + j]);}
private:
	//int i;
	//int posX, posY, posZ;
	int terraintexture;
	

	//GLuint texture[1];		// Storage For One Texture

	int mapSize;			// Size Of Our .RAW Height Map
	float stepSize;			// Width And Height Of Each Quad 
							// ( low value more smooth if 1 it's mean vertex every pixel)
	//float heightRatio;		// Ratio That The Y Is Scaled According To The X And Z
	

	bool keys[256]; // Array Used For The Keyboard Routine
	bool WireRender; // Polygon Flag Set To TRUE By Default
	GLubyte* HeightMap; // Holds The Height Map Data
};