#include "Terrain.h"

Terrain::Terrain(int mapSize, float stepSize)
{
	this->mapSize = mapSize;
	this->stepSize = stepSize;

	scaleValue = 0.6f;	
	HeightMap = new BYTE[mapSize * mapSize];
}

int Terrain::getMapSize() 
{ return mapSize; }

float Terrain::getStepSize()
{ return stepSize; }

GLubyte* Terrain::getHeightMap() 
{ return HeightMap; }

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

void Terrain::LoadTexture(char *filename) 
{
	texture.loadTexture(filename, 255);
}

void Terrain::Draw(float posX, float posY, float posZ)
{
	glGenLists(1);
	glNewList(terrainList,GL_COMPILE);
	glPushMatrix();
		// GL Material
		GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat LightSpecular[] =   { 1.0, 1.0, 1.0, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, LightAmbient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, LightDiffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LightSpecular);

		glScaled(4, 4, 4);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture.getTexture());
		glScalef(1, scaleValue, 1);
		glTranslatef(-mapSize/2.0, 0, -mapSize/2.0);
		for (int i = 3 ; i<mapSize-3 ; i++)
		{
			glBegin(GL_QUAD_STRIP);
			for (int j=3 ; j<=mapSize-3 ; j++)
			{
				glTexCoord2f(j*stepSize, i*stepSize);
				glVertex3f(j+posX, GetValue(j,i)+posY, i+posZ);
			
				glTexCoord2f(j*stepSize, (i+1)*stepSize);
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
{}
