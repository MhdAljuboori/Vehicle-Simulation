#pragma once

#include <windows.h> // Header File For Windows
#include <stdio.h> // Header file For Standard Input/Output
#include <gl\gl.h> // Header File For The OpenGL32 Library
#include <gl\glu.h> // Header File For The GLu32 Library
#include <gl\glaux.h> // Header File For The Glaux Library

class Terrain
{
public:
	Terrain(bool keys, int mapSize = 1024);
	~Terrain(void);

	// Loads The .RAW File And Stores It In pHeightMap
	void LoadRawFile(LPSTR strName, int nSize, BYTE *pHeightMap);

	//get methods
	int getMapSize();
	BYTE* getG_HeightMap();
private:
	int mapSize;

	bool keys[256]; // Array Used For The Keyboard Routine
	bool bRender; // Polygon Flag Set To TRUE By Default
	BYTE* g_HeightMap; // Holds The Height Map Data
	float scaleValue; // Scale Value For The Terrain

	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Declaration For WndProc
};

