#include "Terrain.h"

#define STEP_SIZE 16 // Width And Height Of Each Quad ( NEW )
#define HEIGHT_RATIO 1.5f // Ratio That The Y Is Scaled According To The X And Z ( NEW )

Terrain::Terrain(bool keys, int mapSize)
{
	//hDC = NULL;
	//hWnd = NULL;
	//hRC = NULL;
	this->mapSize = mapSize;

	bRender = TRUE;
	scaleValue = 0.15f;	
	g_HeightMap = new BYTE[mapSize * mapSize];
}

int Terrain::getMapSize() 
{ return mapSize; }

BYTE* Terrain::getG_HeightMap() 
{ return g_HeightMap; }

void Terrain::LoadRawFile(LPSTR strName, int nSize, BYTE *pHeightMap)
{
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
	fread( pHeightMap, 1, nSize, pFile );

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

int Terrain::Height(BYTE *pHeightMap, int X, int Y)
{
	int x = X % mapSize; // Error Check Our x Value
	int y = Y % mapSize; // Error Check Our y Value
	if(!pHeightMap) return 0; // Make Sure Our Data Is Valid

	// Index Into Our Height Array And Return The Height
	// The same of pHeightMap[x][y] if pHeightMap is 2D array
	return pHeightMap[x + (y * mapSize)];
}

void Terrain::SetVertexColor(BYTE *pHeightMap, int x, int y)
{
	// Depending On The Height Index
	if(!pHeightMap) return; // Make Sure Our Height Data Is Valid

	float fColor = -0.15f + (Height(pHeightMap, x, y ) / 256.0f);
	
	// Assign This Blue Shade To The Current Vertex
	glColor3f(0.0f, 0.0f, fColor );
}

Terrain::~Terrain(void)
{
}
