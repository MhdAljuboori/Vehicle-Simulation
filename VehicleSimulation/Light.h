#ifndef LIGHT_H
#define LIGHT_H

#include<Windows.h>
#include "gltexture.h"
#include <gl/GL.H>

enum LightType { Directional , Spot };

class Light
{
public:
	Light();
	Light(float* amb, float* spe, float* dif, float* pos, 
		float* spotdir, float spotcut, GLenum lightName);
	Light(float* amb, float* spe, float* dif, float* pos, GLenum lightName);
	void setUpLight();

	void setAmbient(float x,float y,float z,float w);
	void setSpecular(float x,float y,float z,float w);
	void setDiffuse(float x,float y,float z,float w);
	void setPosition(float x,float y,float z,float w);
	void setSpotDirection(float x,float y,float z,float w);

	float* getAmbient() { return &ambient[0]; }
	float* getSpecular() { return &specular[0]; }
	float* getDiffuse() { return &diffuse[0]; }
	float* getPosition() { return &position[0]; }

	bool isLightOn() { return lightOn; }

	void enableLight();
	void disableLight();

private:
	float ambient[4];
	float specular[4];
	float diffuse[4];
	float position[4];
	float spotDirection[4];
	float spotCutOff;

	LightType lightType;
	GLenum lightName;

	bool lightOn;
};


#endif