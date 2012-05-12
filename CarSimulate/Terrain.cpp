#include "Terrain.h"

Terrain::Terrain(bool keys, int &texture_num, int mapSize, float stepSize)
{
	this->mapSize = mapSize;
	this->stepSize = stepSize;
	
	//terraintexture = texture_num;
	//texture_num++;
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

void Terrain::LoadTexture(char *filename) 
{
	texture.loadTexture(filename, 255);
}

Vector3D Terrain::CalcNormal(Vector3D v1, Vector3D v2, Vector3D v3)
 {
  double v1x,v1y,v1z,v2x,v2y,v2z;
  double nx,ny,nz;
  double vLen;
 
  Vector3D Result;
 
  // Calculate vectors
  v1x = v1.getX() - v2.getX();
  v1y = v1.getY() - v2.getY();
  v1z = v1.getZ() - v2.getZ();
 
  v2x = v2.getX() - v3.getX();
  v2y = v2.getY() - v3.getY();
  v2z = v2.getZ() - v3.getZ();
 
  // Get cross product of vectors
  nx = (v1y * v2z) - (v1z * v2y);
  ny = (v1z * v2x) - (v1x * v2z);
  nz = (v1x * v2y) - (v1y * v2x);
 
  // Normalise final vector
  vLen = sqrt( (nx * nx) + (ny * ny) + (nz * nz) );
 
  Result.setX((float)(nx / vLen));
  Result.setY((float)(ny / vLen));
  Result.setZ((float)(nz / vLen));
 
  return Result;
}

void Terrain::Draw(float posX, float posY, float posZ)
{
	glGenLists(1);
	glNewList(terrainList,GL_COMPILE);
	glPushMatrix();
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
			Vector3D normal;
			if (j+1 <=mapSize-3)
				normal = CalcNormal(Vector3D(j+posX, GetValue(j,i)+posY, i+posZ), 
							Vector3D(j+posX, GetValue(j,i+1)+posY, i+1+posZ), 
							Vector3D(j+1+posX, GetValue(j+1,i)+posY, i+posZ));

			glNormal3f(normal.getX(), normal.getY(), normal.getZ());
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
