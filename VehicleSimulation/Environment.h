#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Terrain.h"
#include "SkyBox.h"
#include "Vector3D.h"
#include "gltexture.h"

class Environment
{

public:
	Environment();

	Terrain* getTerrain() { return terrain; }
	SkyBox* getSkyBox() { return skyBox; }

	void draw();
	void loadContents();
	void unloadContents();

private:
	Terrain* terrain;
	SkyBox* skyBox;
};
	

#endif