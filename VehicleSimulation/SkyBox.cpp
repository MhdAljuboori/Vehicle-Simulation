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

SkyBox::SkyBox(char* toppath,char* bottompath, char* leftpath, char* rightpath, 
	char* frontpath, char* backpath)
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
		// Front Face
	   glBegin(GL_QUADS);
			glNormal3f( 0.0f, 0.0f, 0.5f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1000.0f, -1000.0f,  1000.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1000.0f, -1000.0f,  1000.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1000.0f,  1000.0f,  1000.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1000.0f,  1000.0f,  1000.0f);
		
		glEnd();
		// Back Face
		glBindTexture(GL_TEXTURE_2D,back.getTexture());
	    glBegin(GL_QUADS);
			glNormal3f( 0.0f, 0.0f,-0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1000.0f, -1000.0f, -1000.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1000.0f,  1000.0f, -1000.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1000.0f,  1000.0f, -1000.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1000.0f, -1000.0f, -1000.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,top.getTexture());
		// Top Face
		glBegin(GL_QUADS);
		    glNormal3f( 0.0f, 0.5f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1000.0f,  1000.0f, -1000.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1000.0f,  1000.0f,  1000.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1000.0f,  1000.0f,  1000.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1000.0f,  1000.0f, -1000.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,bottom.getTexture());
		// Bottom Face
		glBegin(GL_QUADS);
			glNormal3f( 0.0f,-0.5f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1000.0f, -1000.0f, -1000.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1000.0f, -1000.0f, -1000.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1000.0f, -1000.0f,  1000.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1000.0f, -1000.0f,  1000.0f);
		
		glEnd();
		glBindTexture(GL_TEXTURE_2D,right.getTexture());
		// Right Face
		glBegin(GL_QUADS);
			glNormal3f( 0.5f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1000.0f, -1000.0f, -1000.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1000.0f,  1000.0f, -1000.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1000.0f,  1000.0f,  1000.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1000.0f, -1000.0f,  1000.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,left.getTexture());
		// Left Face
		glBegin(GL_QUADS);
			glNormal3f(-0.5f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1000.0f, -1000.0f, -1000.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1000.0f, -1000.0f,  1000.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1000.0f,  1000.0f,  1000.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1000.0f,  1000.0f, -1000.0f);
		glEnd();

	glPopMatrix();
}
