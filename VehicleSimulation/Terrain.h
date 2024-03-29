#pragma once

#include <stdio.h>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <iostream>
#include "Vector3D.h"
#include "Texture.h"

class Terrain
{
public:
	Terrain(int mapSize = 512, float stepSize = 1/512.0);
	~Terrain(void);

	//get methods
	int getMapSize();
	float getStepSize();
	GLubyte* getHeightMap();

	void Draw(float posX=0, float posY=0, float posZ=0);
	void draw();

	float scaleValue;		// Scale Value For The Terrain
	
	// Load Bitmaps And Convert To Textures
	void LoadTexture(char *filename);

	// Loads The File And Stores It In g_HeightMap
	void LoadHeightMap(char *filename);

	inline GLubyte GetValue(int i ,int j  )  
		{return (int)(HeightMap[i*mapSize + j]);}
private:
	Texture texture;
	GLuint terrainList;

	int mapSize;			// Size Of Our .RAW Height Map
	float stepSize;			// Width And Height Of Each Quad 
							// ( low value more smooth if 1 it's mean vertex every pixel)

	bool keys[256];			// Array Used For The Keyboard Routine
	GLubyte* HeightMap;		// Holds The Height Map Data
};