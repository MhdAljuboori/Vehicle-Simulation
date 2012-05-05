#include "SkyBox.h"


SkyBox::SkyBox(int &texture_num, char* filenameBack, char* filenameFront, char* filenameTop, 
			char* filenameDown, char* filenameRight, char* filenameLeft)
{
	// number of textures
	num_texture = texture_num;
	texture_num += 6;
	
	// Enable Texture
	glEnable(GL_TEXTURE_2D);

	// load Texture
	back = LoadTexture(filenameBack);
	front = LoadTexture(filenameFront);
	top = LoadTexture(filenameTop);
	down = LoadTexture(filenameDown);
	right = LoadTexture(filenameRight);
	left = LoadTexture(filenameLeft);
}

int SkyBox::LoadTexture(char *filename,int alpha)
{
	int i, j=0; //Index variables
    FILE *l_file; //File pointer
    unsigned char *l_texture; //The pointer to the memory zone in which we will load the texture
     
    // windows.h gives us these types to work with the Bitmap files
    BITMAPFILEHEADER fileheader; 
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    num_texture++; // The counter of the current texture is increased

    if( (l_file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading
    
    fread(&fileheader, sizeof(fileheader), 1, l_file); // Read the fileheader
    
    fseek(l_file, sizeof(fileheader), SEEK_SET); // Jump the fileheader
    fread(&infoheader, sizeof(infoheader), 1, l_file); // and read the infoheader

    // Now we need to allocate the memory for our image (width * height * color deep)
    l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    // And fill it with zeros
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
 
    // At this point we can read every pixel of the image
    for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
    {            
            // We load an RGB value from the file
            fread(&rgb, sizeof(rgb), 1, l_file); 

            // And store it
            l_texture[j+0] = rgb.rgbtRed; // Red component
            l_texture[j+1] = rgb.rgbtGreen; // Green component
            l_texture[j+2] = rgb.rgbtBlue; // Blue component
            l_texture[j+3] = alpha; // Alpha value
            j += 4; // Go to the next position
    }

    fclose(l_file); // Closes the file stream
     
    glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //The minifying function

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECR );

    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture); // Free the memory we used to load the texture

    return (num_texture); // Returns the current texture OpenGL ID
}

void SkyBox::DrawFace()
{
	glBegin(GL_QUADS);

		//front
		glVertex3f(0.5,-0.5,0.5);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(-0.5,0.5,0.5);
		glVertex3f(-0.5,-0.5,0.5);

		//back
		glVertex3f(0.5,-0.5,-0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(-0.5,0.5,-0.5);
		glVertex3f(-0.5,-0.5,-0.5);

		//right
		glVertex3f(0.5,-0.5,-0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(0.5,-0.5,0.5);

		//left
		glVertex3f(-0.5,-0.5,0.5);
		glVertex3f(-0.5,0.5,0.5);
		glVertex3f(-0.5,0.5,-0.5);
		glVertex3f(-0.5,-0.5,-0.5);

		//up
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(-0.5,0.5,-0.5);
		glVertex3f(-0.5,0.5,0.5);

		//down
		glVertex3f(0.5,-0.5,-0.5);
		glVertex3f(0.5,-0.5,0.5);
		glVertex3f(-0.5,-0.5,0.5);
		glVertex3f(-0.5,-0.5,-0.5);

	glEnd();
}

void SkyBox::DrawCube(float xPos, float yPos,  float zPos, float xSize, 
		float ySize,  float zSize, float xRot, float yRot,  float zRot, 
		float R , float G , float B, GLenum mode)
{
	glPushMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, mode);
		glTranslatef(xPos, yPos, zPos);
		glRotatef(xRot, 1, 0, 0);
		glRotatef(yRot, 0, 1, 0);
		glRotatef(zRot, 0, 0, 1);
		glScalef(xSize, ySize, zSize);
		glColor3f(R, G, B);
		DrawFace();
	glPopMatrix();
}

/*
void DrawPlanet(float radius , float th)
{
	glPushMatrix();
		glRotatef(th , 0,1,0);
		glRotatef(90,1,0,0);
		gluSphere(quadric,radius,32,32);
	glPopMatrix();
}

void DrawOrbit(float radius)
{
		glBegin(GL_LINE_LOOP);
		for(float f = 0.0 ; f<6.28 ; f+=0.01)
		{
			x=radius*cos(f);
			z=radius*sin(f);
			glVertex3f(x,0,z);
		}
	glEnd();
}
*/

void SkyBox::Draw()
{
	glPushMatrix();
		glScalef(4000, 4000, 4000);
	
		glBindTexture(GL_TEXTURE_2D,front);
		glBegin(GL_QUADS);
			//front
			glTexCoord2f(1,0) ; 	glVertex3f(0.5,-0.5,0.5); 
			glTexCoord2f(1,1) ;		glVertex3f(0.5,0.5,0.5);
			glTexCoord2f(0,1) ;		glVertex3f(-0.5,0.5,0.5);
			glTexCoord2f(0,0) ;		glVertex3f(-0.5,-0.5,0.5);
		glEnd();
	
		glBindTexture(GL_TEXTURE_2D,back);
		glBegin(GL_QUADS);
			//back
			glTexCoord2f(0,0) ;		glVertex3f(0.5,-0.5,-0.5);
			glTexCoord2f(0,1) ;		glVertex3f(0.5,0.5,-0.5);
			glTexCoord2f(1,1) ;		glVertex3f(-0.5,0.5,-0.5);
			glTexCoord2f(1,0) ;		glVertex3f(-0.5,-0.5,-0.5);
		glEnd();
	
		glBindTexture(GL_TEXTURE_2D,right);
		glBegin(GL_QUADS);
			//right
			glTexCoord2f(1,0) ;		glVertex3f(0.5,-0.5,-0.5);
			glTexCoord2f(1,1) ;		glVertex3f(0.5,0.5,-0.5);
			glTexCoord2f(0,1) ;		glVertex3f(0.5,0.5,0.5);
			glTexCoord2f(0,0) ;		glVertex3f(0.5,-0.5,0.5);
		glEnd();
	
		glBindTexture(GL_TEXTURE_2D,left);
		glBegin(GL_QUADS);
			//left
			glTexCoord2f(1,0) ;		glVertex3f(-0.5,-0.5,0.5);
			glTexCoord2f(1,1) ;		glVertex3f(-0.5,0.5,0.5);
			glTexCoord2f(0,1) ;		glVertex3f(-0.5,0.5,-0.5);
			glTexCoord2f(0,0) ;		glVertex3f(-0.5,-0.5,-0.5);
		glEnd();
	
		glBindTexture(GL_TEXTURE_2D,top);
		glBegin(GL_QUADS);
			//up
			glTexCoord2f(1,0) ;		glVertex3f(0.5,0.5,0.5);
			glTexCoord2f(1,1) ;		glVertex3f(0.5,0.5,-0.5);
			glTexCoord2f(0,1) ;		glVertex3f(-0.5,0.5,-0.5);
			glTexCoord2f(0,0) ;		glVertex3f(-0.5,0.5,0.5);
		glEnd();
	
		glBindTexture(GL_TEXTURE_2D,down);
		glBegin(GL_QUADS);
			//down
			glTexCoord2f(1,0) ;		glVertex3f(0.5,-0.5,-0.5);
			glTexCoord2f(1,1) ;		glVertex3f(0.5,-0.5,0.5);
			glTexCoord2f(0,1) ;		glVertex3f(-0.5,-0.5,0.5);
			glTexCoord2f(0,0) ;		glVertex3f(-0.5,-0.5,-0.5);
		glEnd();
	glPopMatrix();
}

SkyBox::~SkyBox(void)
{
}
