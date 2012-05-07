#ifndef TEXTURE_H
#define TEXTURE_H

#include<windows.h>
#include<gl.h>
#include<glaux.h>
#include<MMSystem.h>
#include<gameux.h>

class Texture 
{
public:
	Texture();
	Texture(GLuint text);

	GLuint getTexture();
	void setTexture(GLuint text);
	bool loadTexture(char* textruepath);


private:
	GLuint texture;
};


#endif