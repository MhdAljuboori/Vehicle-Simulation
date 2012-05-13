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
	glEnable(lightName);
}

Light::Light(float* amb, float* spe, float* dif, float* pos,
			LightType lightTy, float* spotdir, float spotcut)
{
	for(int i = 0; i<4; i++)
	{
		ambient[i] = amb[i];
		specular[i] = spe[i];
		diffuse[i] = dif[i];
		position[i] = pos[i];
		spotDirection[i] = spotdir[i];
	}

	lightType = lightTy;
	spotCutOff = spotcut;
	glEnable(lightName);
}


void Light::setUpLight()
{
	if( lightType == Spot)
	{
		glLightfv(lightName,GL_AMBIENT,&ambient[0]);
		glLightfv(lightName,GL_SPECULAR,&specular[0]);
		glLightfv(lightName,GL_DIFFUSE,&diffuse[0]);
		glLightfv(lightName,GL_POSITION,&position[0]);
		glLightfv(lightName,GL_SPOT_DIRECTION,&spotDirection[0]);
		glLightf(lightName,GL_SPOT_CUTOFF,spotCutOff);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
		glEnable(lightName);
	}

	else
	{
		glLightfv(lightName,GL_AMBIENT,&ambient[0]);
		glLightfv(lightName,GL_SPECULAR,&specular[0]);
		glLightfv(lightName,GL_DIFFUSE,&diffuse[0]);
		glLightfv(lightName,GL_POSITION,&position[0]);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
		glEnable(lightName);
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
	if((lightType == Spot) && (w >0 && w<1))
	{
		position[3] = w;
	}
	else
		if( (lightType == Directional) && (w == 0))
		{
			position[3] = w;
		}
		else
			position[3] = 0;
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