#include "Light.h"

Light::Light()
{
	for(int i=0;i<4;i++)
	{
		ambient[i] = 0.5;
		specular[i] = 0.5;
		diffuse[i] = 0.5;
		position[i] = 0;
		spotDirection[i] = 0;
	}
	spotCutOff = 0;
	lightType = Spot;
	lightName = GL_LIGHT0;
	disableLight();
}

Light::Light(float* amb, float* spe, float* dif, float* pos, 
	float* spotdir, float spotcut, GLenum lightName)
{
	for(int i = 0; i<4; i++)
	{
		ambient[i] = amb[i];
		specular[i] = spe[i];
		diffuse[i] = dif[i];
		position[i] = pos[i];
		spotDirection[i] = spotdir[i];
	}
	lightType = Spot;
	spotCutOff = spotcut;
	this->lightName = lightName;
	disableLight();
}

Light::Light(float* amb, float* spe, float* dif, float* pos, GLenum lightName)
{
	for(int i = 0; i<4; i++)
	{
		ambient[i] = amb[i];
		specular[i] = spe[i];
		diffuse[i] = dif[i];
		position[i] = pos[i];
	}
	lightType = Directional;
	this->lightName = lightName;
	disableLight();
}


void Light::setUpLight()
{
	if( lightType == Spot)
	{
		glLightfv(lightName,GL_AMBIENT,ambient);
		glLightfv(lightName,GL_SPECULAR,specular);
		glLightfv(lightName,GL_DIFFUSE,diffuse);
		glLightfv(lightName,GL_POSITION,position);
		glLightfv(lightName,GL_SPOT_DIRECTION,spotDirection);
		glLightf(lightName,GL_SPOT_CUTOFF,spotCutOff);
		//glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
		//glEnable(lightName);
	}

	else
	{
		glLightfv(lightName,GL_AMBIENT,ambient);
		glLightfv(lightName,GL_SPECULAR,specular);
		glLightfv(lightName,GL_DIFFUSE,diffuse);
		glLightfv(lightName,GL_POSITION,position);
		//glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
		//glEnable(lightName);
	}
}

void Light::setAmbient(float x,float y,float z,float w)
{
	ambient[0] = x;
	ambient[1] = y;
	ambient[2] = z;
	ambient[3] = w;
}

void Light::setSpecular(float x,float y,float z,float w)
{
	specular[0] = x;
	specular[1] = y;
	specular[2] = z;
	specular[3] = w;
}

void Light::setDiffuse(float x,float y,float z,float w)
{
	diffuse[0] = x;
	diffuse[1] = y;
	diffuse[2] = z;
	diffuse[3] = w;
}

void Light::setPosition(float x,float y,float z,float w)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
	position[3] = w;
}

void Light::setSpotDirection(float x,float y,float z,float w)
{
	spotDirection[0] = x;
	spotDirection[1] = y;
	spotDirection[2] = z;
	spotDirection[3] = w;
}

void Light::enableLight()
{
	lightOn = true;
	glEnable(lightName);
}

void Light::disableLight()
{
	lightOn = false;
	glDisable(lightName);
}