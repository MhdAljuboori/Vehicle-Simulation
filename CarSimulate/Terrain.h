#pragma once

#include <stdio.h>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <iostream>

class Terrain
{
public:
	Terrain(bool keys, int mapSize = 512, float stepSize = 1/512.0);
	~Terrain(void);

	//get methods
	int getMapSize();
	float getStepSize();
	GLubyte* getHeightMap();

	void Draw();

	float scaleValue;		// Scale Value For The Terrain

	void setWire();
	void setPolygon();
	void setWireNot();

	bool IsPolygon();
	
	// Load Bitmaps And Convert To Textures
	void LoadTexture(char *filename,int alpha=255);

	// Loads The File And Stores It In g_HeightMap
	void LoadHeightMap(char *filename);

	inline GLubyte GetValue(int i ,int j  )  
		{return (int)(HeightMap[i*mapSize + j]);}
private:
	int terraintexture;

	int mapSize;			// Size Of Our .RAW Height Map
	float stepSize;			// Width And Height Of Each Quad 
							// ( low value more smooth if 1 it's mean vertex every pixel)
	

	bool keys[256]; // Array Used For The Keyboard Routine
	bool WireRender; // Polygon Flag Set To TRUE By Default
	GLubyte* HeightMap; // Holds The Height Map Data
};