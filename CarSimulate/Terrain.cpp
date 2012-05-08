#include "Terrain.h"

Terrain::Terrain(bool keys, int &texture_num, int mapSize, float stepSize)
{
	this->mapSize = mapSize;
	this->stepSize = stepSize;
	
	terraintexture = texture_num;
	texture_num++;
	WireRender = FALSE;
	scaleValue = 0.6f;	
	HeightMap = new BYTE[mapSize * mapSize];
}

int Terrain::getMapSize() 
{ return mapSize; }

float Terrain::getStepSize()
{ return stepSize; }

GLubyte* Terrain::getHeightMap() 
{ return HeightMap; }

void Terrain::setWire()
{ WireRender = FALSE; }

void Terrain::setPolygon()
{ WireRender = TRUE; }

void Terrain::setWireNot()
{ WireRender != WireRender; }

bool Terrain::IsPolygon()
{ return WireRender; }

void Terrain::LoadHeightMap(char *filename)
{
    int i, j=0;
	    FILE *textureFile;

    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;

	// Check To See If We Found The File And Could Open It
	if( (textureFile = fopen(filename, "rb"))==NULL) 
	{
		// Display Error Message And Stop The Function
		MessageBox(NULL, "Can't Find The Height Map!", "Error", MB_OK);
		return;
	}

	// Here We Load The File Into Our HeightMap Data Array
	fread(&fileheader, sizeof(fileheader), 1, textureFile);

    fseek(textureFile, sizeof(fileheader), SEEK_SET);

    fread(&infoheader, sizeof(infoheader), 1, textureFile);

	HeightMap = new GLubyte[infoheader.biWidth * infoheader.biHeight];

	fread(HeightMap, sizeof(GLubyte), infoheader.biWidth*infoheader.biHeight, textureFile);

    fclose(textureFile);
}

void Terrain::LoadTexture(char *filename,int alpha) 
{
	//int num_texture = -1;
    int i, j=0; //Index variables
    FILE *l_file; //File pointer
    unsigned char *l_texture; //The pointer to the memory zone in which we will load the texture
     
    // windows.h gives us these types to work with the Bitmap files
    BITMAPFILEHEADER fileheader; 
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

	terraintexture++; // The counter of the current texture is increased
	
	// Open the file for reading
    if( (l_file = fopen(filename, "rb"))==NULL) 
	{
		terraintexture = -1;
	}
    
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
     
	glBindTexture(GL_TEXTURE_2D, terraintexture); // Bind the ID texture specified by the 2nd parameter

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
}

void Terrain::Draw(float posX, float posY, float posZ)
{
	glGenLists(1);
	glNewList(terrainList,GL_COMPILE);
	glPushMatrix();
	glScaled(4, 4, 4);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, terraintexture);
	glScalef(1, scaleValue, 1);
	glTranslatef(-mapSize/2.0, 0, -mapSize/2.0);
	for (int i = 3 ; i<mapSize-3 ; i++)
	{
		glBegin(GL_QUAD_STRIP);
		for (int j=3 ; j<=mapSize-3 ; j++)
		{
			glTexCoord2f(j*stepSize,i*stepSize);
			glVertex3f(j+posX, GetValue(j,i)+posY, i+posZ);
			
			glTexCoord2f(j*stepSize,(i+1)*stepSize);
			glVertex3f(j+posX, GetValue(j,i+1)+posY, i+1+posZ);
		}
		glEnd();
	}
	glPopMatrix();
	glEndList();
}

void Terrain::draw()
{
	glCallList(terrainList);
}
Terrain::~Terrain(void)
{
}
