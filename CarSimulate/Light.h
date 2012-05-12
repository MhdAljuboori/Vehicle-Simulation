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
	Light(float* ambient,float* specular,float* diffuse,float* position,LightType lightType,float* spotdir,float spotcutoff);
	void setUpLight();

	void setAmbient(float x,float y,float z,float w);
	void setSpecular(float x,float y,float z,float w);
	void setDiffuse(float x,float y,float z,float w);
	void setPosition(float x,float y,float z,float w);

	float* getAmbient() { return &ambient[0]; }
	float* getSpecular() { return &specular[0]; }
	float* getDiffuse() { return &diffuse[0]; }
	float* getPosition() { return &position[0]; }

	bool getLightState() { return lightOn; }

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