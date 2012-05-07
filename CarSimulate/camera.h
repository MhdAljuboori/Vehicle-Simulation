#ifndef CAMERA_H
#define CAMERA_H

#include <gl/glut.h>		
#include "vector3D.h"

#define PI 3.1415265359
#define PIdiv180 3.1415265359/180.0

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

class CCamera
{
private:
	Vector3D Position;
	Vector3D ViewDir;		/*Not used for rendering the camera, but for "moveforwards"
							So it is not necessary to "actualize" it always. It is only
							actualized when ViewDirChanged is true and moveforwards is called*/
	bool ViewDirChanged;
	GLfloat RotatedX, RotatedY, RotatedZ;	
	void GetViewDir ( void );
public:
	CCamera();				//inits the values (Position: (0|0|0) Target: (0|0|-1) )
	void Render ( void );	//executes some glRotates and a glTranslate command
							//Note: You should call glLoadIdentity before using Render
	void Move ( Vector3D& Direction );
	void RotateX ( GLfloat Angle );
	void RotateY ( GLfloat Angle );
	void RotateZ ( GLfloat Angle );
	void RotateXYZ ( Vector3D Angles );
	void MoveForwards ( GLfloat Distance );
	void StrafeRight ( GLfloat Distance );
};

#endif