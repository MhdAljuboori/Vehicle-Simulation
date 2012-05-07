#include "Texture.h"
#include<stdio.h>
#include<cstring>
#include<cmath>

Texture::Texture()
{
	texture = 0 ;
}

Texture::Texture(GLuint text)
{
	texture = text ;
}

GLuint Texture::getTexture()
{
	return texture;
}

void Texture::setTexture(GLuint text)
{
	texture = text ;
}

bool Texture::loadTexture(char* texturepath)
{
	AUX_RGBImageRec* image ;
	image = new AUX_RGBImageRec();

	FILE* file = NULL ;
	if(!texturepath)
		return false;
	file = fopen(texturepath , "r");
	if(file)
	{
		fclose(file);
		image = auxDIBImageLoad(texturepath);
	}

	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->sizeX,image->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,image->data);

	if(image)
	{
		if(image->data)
			free(image->data);
		free(image);
	}
	return true;
}


