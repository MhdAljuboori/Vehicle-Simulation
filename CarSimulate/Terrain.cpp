#include "Terrain.h"

Terrain::Terrain(bool keys, int posX, int posY, int posZ,
	int mapSize, int stepSize, float heightRatio)
{
	if (!LoadGLTextures()) // Jump To Texture Loading Routine ( NEW )
		return; // If Texture Didn't Load Return FALSE ( NEW )

	this->mapSize = mapSize;
	this->stepSize = stepSize;
	this->heightRatio = heightRatio;
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;

	bRender = TRUE;
	scaleValue = 0.15f;	
	g_HeightMap = new BYTE[mapSize * mapSize];
}

int Terrain::getMapSize() 
{ return mapSize; }

int Terrain::getStepSize()
{ return stepSize; }

float Terrain::getHeightRatio()
{ return heightRatio; }

BYTE* Terrain::getG_HeightMap() 
{ return g_HeightMap; }

void Terrain::setWire()
{ bRender = FALSE; }

void Terrain::setPolygon()
{ bRender = TRUE; }

void Terrain::setWireNot()
{ bRender != bRender; }

bool Terrain::IsPolygon()
{ return bRender; }

void Terrain::LoadRawFile(LPSTR strName)
{
	int nSize = mapSize * mapSize;
	FILE *pFile = NULL;
	// Open The File In Read / Binary Mode.
	pFile = fopen( strName, "rb" );

	// Check To See If We Found The File And Could Open It
	if ( pFile == NULL )
	{
		// Display Error Message And Stop The Function
		MessageBox(NULL, "Can't Find The Height Map!", "Error", MB_OK);
		return;
	}

	// Here We Load The .RAW File Into Our pHeightMap Data Array
	// We Are Only Reading In '1', And The Size Is (Width * Height)
	fread( g_HeightMap, 1, nSize, pFile );

	// After We Read The Data, It's A Good Idea To Check If Everything Read Fine
	int result = ferror( pFile );

	// Check If We Received An Error
	if (result)
	{
		MessageBox(NULL, "Failed To Get Data!", "Error", MB_OK);
	}

	// Close The File
	fclose(pFile);
}

AUX_RGBImageRec* Terrain::LoadBMP(char *Filename)
{
	FILE *File=NULL;	// File Handle
	
	if (!Filename)		// Make Sure A Filename Was Given
		return NULL;	// If Not Return NULL

	File = fopen(Filename, "r"); // Check To See If The File Exists
	if (File) // Does The File Exist?
	{
		fclose(File); // Close The Handle
		return auxDIBImageLoad(Filename); // Load The Bitmap And Return A Pointer
	}

	return NULL; // If Load Failed Return NULL
}

int Terrain::LoadGLTextures()
{
	int Status=FALSE; // Status Indicator

	AUX_RGBImageRec *TextureImage[1]; // Create Storage Space For The Texture

	memset(TextureImage,0,sizeof(void *)*1); // Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0]=LoadBMP("Data/Net.bmp"))
	{
		Status=TRUE; // Set The Status To TRUE
		glGenTextures(1, &texture[0]); // Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		// Generate The Texture
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, TextureImage[0]->data);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering
	}

	if (TextureImage[0]) // If Texture Exists
	{
		if (TextureImage[0]->data) // If Texture Image Exists
			free(TextureImage[0]->data); // Free The Texture Image Memory
		free(TextureImage[0]); // Free The Image Structure
	}

	return Status; // Return The Status
}

int Terrain::Height(int X, int Y)
{
	int x = X % mapSize; // Error Check Our x Value
	int y = Y % mapSize; // Error Check Our y Value
	if(!g_HeightMap) return 0; // Make Sure Our Data Is Valid

	// Index Into Our Height Array And Return The Height
	// The same of pHeightMap[x][y] if pHeightMap is 2D array
	return g_HeightMap[x + (y * mapSize)];
}

void Terrain::SetVertexColor(int x, int y)
{
	// Depending On The Height Index
	if(!g_HeightMap) return; // Make Sure Our Height Data Is Valid

	float fColor = -0.15f + (Height(x, y) / 256.0f);
	
	// Assign This Blue Shade To The Current Vertex
	/*
	if (i == 0)
		glTexCoord2f(0.0f, 0.0f);
	if (i == 100)
		glTexCoord2f(0.0f, 1);
	if (i == 500)
		glTexCoord2f(1, 0);
	if (i == 1000)
		glTexCoord2f(1, 1);
	i++;*/
	glColor3f(0, fColor, 0);
}

void Terrain::RenderHeightMap()
{
	//i=0;
	int X = 0, Y = 0; // Create Some Variables To Walk The Array With.
	int x, y, z; // Create Some Variables For Readability
	if(!g_HeightMap) return; // Make Sure Our Height Data Is Valid

	// What We Want To Render
	if(bRender)
		glBegin( GL_QUADS ); // Render Polygons
	else
		glBegin( GL_LINES ); // Render Lines Instead

	// Walk the array of height data and pluck out some heights to plot our points
	for (X = 0; X < mapSize; X += stepSize)
	{
		for (Y = 0; Y < mapSize; Y += stepSize)
		{

			//////////Begin Draw First Vertex//////////
			// Get The (X, Y, Z) Value For The Bottom Left Vertex
			x = X;
			y = Height(X, Y);
			z = Y;

			// Set The Color Value Of The Current Vertex
			SetVertexColor(x, z);
			// Send This Vertex To OpenGL To Be Rendered
			glVertex3i(x + posX, y + posY, z + posZ);
			//////////End Draw First Vertex//////////

			//////////Begin Draw Second Vertex//////////
			// Get The (X, Y, Z) Value For The Top Left Vertex
			x = X;
			y = Height(X, Y + stepSize);
			z = Y + stepSize;

			// Set The Color Value Of The Current Vertex
			SetVertexColor(x, z);
			// Send This Vertex To OpenGL To Be Rendered
			glVertex3i(x + posX, y + posY, z + posZ);
			//////////End Draw Second Vertex//////////

			//////////Begin Draw Third Vertex//////////
			// Get The (X, Y, Z) Value For The Top Right Vertex
			x = X + stepSize;
			y = Height(X + stepSize, Y + stepSize);
			z = Y + stepSize;

			// Set The Color Value Of The Current Vertex
			SetVertexColor(x, z);
			// Send This Vertex To OpenGL To Be Rendered
			glVertex3i(x + posX, y + posY, z + posZ);
			//////////End Draw Third Vertex//////////

			//////////Begin Draw fourth Vertex//////////
			// Get The (X, Y, Z) Value For The Bottom Right Vertex
			x = X + stepSize;
			y = Height(X + stepSize, Y );
			z = Y;

			// Set The Color Value Of The Current Vertex
			SetVertexColor(x, z);
			// Send This Vertex To OpenGL To Be Rendered
			glVertex3i(x + posX, y + posY, z + posZ); 
			//////////End Draw fourth Vertex//////////
		}
	}
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Reset The Color
}

void Terrain::Draw()
{
	glPushMatrix();
	glScalef(scaleValue, scaleValue * heightRatio, scaleValue);
	glBindTexture(GL_TEXTURE_2D, texture[0]); // Select Our Texture
	RenderHeightMap();
	glPopMatrix();
}

Terrain::~Terrain(void)
{
}
