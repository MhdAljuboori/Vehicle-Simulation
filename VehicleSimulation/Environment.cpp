#include "Environment.h"

Environment::Environment()
{
	int texnum;
	terrain = new Terrain(false,texnum);
	skyBox = new SkyBox();
}

void Environment::draw()
{
	glPushMatrix();

	skyBox->draw();
	terrain->draw();

	glPopMatrix();
}

void Environment::loadContents()
{
	terrain->LoadTexture("Data/terrain ground.bmp");
	terrain->LoadHeightMap("Data/terrain height.bmp");
	terrain->Draw();

	skyBox->setTop("data/top1.bmp");
	skyBox->setBottom("data/down.bmp");
	skyBox->setLeft("data/left1.bmp");
	skyBox->setRight("data/right1.bmp");
	skyBox->setFront("data/front1.bmp");
	skyBox->setBack("data/back1.bmp");

}

void Environment::unloadContents()
{
	//////////////////////  unload contents  if nessasry  //////////////

}