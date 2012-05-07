#include "skybox.h"

SkyBox::SkyBox()
{
	top = NULL;
	bottom = NULL;
	left = NULL;
	right = NULL;
	front = NULL;
	back = NULL;
}

SkyBox::SkyBox(char* toppath,char* bottompath,char* leftpath,char* rightpath,char* frontpath,char* backpath)
{
	top.loadTexture(toppath);
	bottom.loadTexture(bottompath);
	left.loadTexture(leftpath);
	right.loadTexture(rightpath);
	front.loadTexture(frontpath);
	back.loadTexture(backpath);
}

void SkyBox::draw()
{
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D,front.getTexture());
	   glBegin(GL_QUADS);
		// Front Face
			glNormal3f( 0.0f, 0.0f, 0.5f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1000.0f, -1000.0f,  1000.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1000.0f, -1000.0f,  1000.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1000.0f,  1000.0f,  1000.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1000.0f,  1000.0f,  1000.0f);
		// Back Face
		glEnd();
	 glBindTexture(GL_TEXTURE_2D,back.getTexture());
	    glBegin(GL_QUADS);
			glNormal3f( 0.0f, 0.0f,-0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1000.0f, -1000.0f, -1000.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1000.0f,  1000.0f, -1000.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1000.0f,  1000.0f, -1000.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1000.0f, -1000.0f, -1000.0f);
		// Top Face
		glEnd();
	 glBindTexture(GL_TEXTURE_2D,top.getTexture());
		glBegin(GL_QUADS);
		    glNormal3f( 0.0f, 0.5f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1000.0f,  1000.0f, -1000.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1000.0f,  1000.0f,  1000.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1000.0f,  1000.0f,  1000.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1000.0f,  1000.0f, -1000.0f);
		// Bottom Face
		glEnd();
	 glBindTexture(GL_TEXTURE_2D,bottom.getTexture());
		glBegin(GL_QUADS);
			glNormal3f( 0.0f,-0.5f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1000.0f, -1000.0f, -1000.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1000.0f, -1000.0f, -1000.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1000.0f, -1000.0f,  1000.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1000.0f, -1000.0f,  1000.0f);
		// Right Face
		glEnd();
	 glBindTexture(GL_TEXTURE_2D,right.getTexture());
		glBegin(GL_QUADS);
			glNormal3f( 0.5f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1000.0f, -1000.0f, -1000.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1000.0f,  1000.0f, -1000.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1000.0f,  1000.0f,  1000.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1000.0f, -1000.0f,  1000.0f);
		// Left Face
		glEnd();
	 glBindTexture(GL_TEXTURE_2D,left.getTexture());
		glBegin(GL_QUADS);
			glNormal3f(-0.5f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1000.0f, -1000.0f, -1000.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1000.0f, -1000.0f,  1000.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1000.0f,  1000.0f,  1000.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1000.0f,  1000.0f, -1000.0f);
		glEnd();

	glPopMatrix();
}
