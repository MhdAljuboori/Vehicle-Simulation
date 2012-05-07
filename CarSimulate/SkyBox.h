#ifndef SKYBOX_H
#define SKYBOX_H

#include <windows.h>
#include "Texture.h"

class SkyBox
{

public:
	SkyBox();
	SkyBox(char* toppath,char* bottompath,char* leftpath,char* rightpath,char* frontpath,char* backpath);
	void draw();
	void setTop(char* path) { top.loadTexture(path); }
	void setBottom(char* path) { bottom.loadTexture(path); }
	void setLeft(char* path) { left.loadTexture(path); }
	void setRight(char* path) { right.loadTexture(path); }
	void setFront(char* path) { front.loadTexture(path); }
	void setBack(char* path) { back.loadTexture(path); }

	GLuint getTop() { return top.getTexture(); }
	GLuint getBottom() { return bottom.getTexture(); }
	GLuint getLeft() { return left.getTexture(); }
	GLuint getRight() { return right.getTexture(); }
	GLuint getFront() { return front.getTexture(); }
	GLuint getBack() { return back.getTexture(); }

	~SkyBox() { }

private:
	Texture top;
	Texture bottom;
    Texture left;
	Texture right;
	Texture front;
	Texture back;
};


#endif