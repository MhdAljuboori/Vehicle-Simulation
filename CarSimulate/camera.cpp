#include "camera.h"
#include "math.h"

/***************************************************************************************/

CCamera::CCamera()
{
	//Init with standard OGL values:
	Position.setVector3D(0,0,0);
	ViewDir.setVector3D(0,0,-1);

	ViewDirChanged = false;
	//Only to be sure:
	RotatedX = RotatedY = RotatedZ = 0.0;
}

void CCamera::GetViewDir( void )
{
	Vector3D Step1, Step2;
	//Rotate around Y-axis:
	Step1.setX( cos( (RotatedY + 90.0) * PIdiv180) ) ;
	Step1.setZ( -sin( (RotatedY + 90.0) * PIdiv180) ) ;
	//Rotate around X-axis:
	double cosX = cos (RotatedX * PIdiv180) ;
	Step2.setX( Step1.getX() * cosX ) ;
	Step2.setZ( Step1.getZ() * cosX ) ;
	Step2.setY( sin(RotatedX * PIdiv180) ) ;
	//Rotation around Z-axis not yet implemented, so:
	ViewDir = Step2 ;
}
void CCamera::Move (Vector3D &Direction)
{
	Position += Direction ;
}

void CCamera::RotateY (GLfloat Angle)
{
	RotatedY += Angle;
	ViewDirChanged = true;
}

void CCamera::RotateX (GLfloat Angle)
{
	RotatedX += Angle;
	ViewDirChanged = true;
}
void CCamera::RotateXYZ(Vector3D Angels)
{
	RotatedX += Angels.getX() ;
	RotatedY += Angels.getY() ;
	ViewDirChanged =true;
}
void CCamera::Render( void )
{
	glRotatef(-RotatedX , 1.0, 0.0, 0.0);
	glRotatef(-RotatedY , 0.0, 1.0, 0.0);
	glRotatef(-RotatedZ , 0.0, 0.0, 1.0);
	glTranslatef( -Position.getX(), -Position.getY(), -Position.getZ() );
}

void CCamera::MoveForwards( GLfloat Distance )
{
	//if (ViewDirChanged)
		GetViewDir();

	Vector3D MoveVector;

	MoveVector = (ViewDir)*(-Distance);
	Position += MoveVector ;
}

void CCamera::StrafeRight ( GLfloat Distance )
{
	if (ViewDirChanged) GetViewDir();
	Vector3D MoveVector;

	MoveVector.setZ( -ViewDir.getX() * -Distance ) ;
	MoveVector.setY( 0.0 ) ;
	MoveVector.setX( ViewDir.getZ() * -Distance ) ;

	Position += MoveVector ;
}