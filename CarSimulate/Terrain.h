#pragma once

#include <windows.h> // Header File For Windows
#include <stdio.h> // Header file For Standard Input/Output
#include <gl\gl.h> // Header File For The OpenGL32 Library
#include <gl\glu.h> // Header File For The GLu32 Library
#include <gl\glaux.h> // Header File For The Glaux Library

class Terrain
{
public:
	Terrain(bool keys, int posX = 0, int posY = 0, int posZ = 0,
			int mapSize = 1024, int stepSize = 16, float heightRatio = 1.5f);
	~Terrain(void);

	//get methods
	int getMapSize();
	int getStepSize();
	float getHeightRatio();
	BYTE* getG_HeightMap();

	// Loads The .RAW File And Stores It In g_HeightMap
	void LoadRawFile(LPSTR strName);

	// This Returns The Height From A Height Map Index
	int Height(int X, int Y);
	// This Sets The Color Value For A Particular Index
	void SetVertexColor(int x, int y);
	// This Renders The Height Map As Quads
	void RenderHeightMap();

	void Draw();

	float scaleValue;		// Scale Value For The Terrain

	void setWire();
	void setPolygon();
	void setWireNot();

	bool IsPolygon();
	
	// Loads A Bitmap Image
	AUX_RGBImageRec* LoadBMP(char *Filename);
	// Load Bitmaps And Convert To Textures
	int LoadGLTextures();
private:
	//int i;
	int posX, posY, posZ;

	GLuint texture[1];		// Storage For One Texture

	int mapSize;			// Size Of Our .RAW Height Map
	int stepSize;			// Width And Height Of Each Quad 
							// ( low value more smooth if 1 it's mean vertex every pixel)
	float heightRatio;		// Ratio That The Y Is Scaled According To The X And Z
	

	bool keys[256]; // Array Used For The Keyboard Routine
	bool bRender; // Polygon Flag Set To TRUE By Default
	BYTE* g_HeightMap; // Holds The Height Map Data


	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Declaration For WndProc
};

