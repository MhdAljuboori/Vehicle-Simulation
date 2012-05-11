#include "camera.h"
#include "math.h"

Camera::Camera(Vector3D pos, Vector3D view)
{
	
	Position = pos;
	View = view;
	Right = Vector3D (1.0, 0.0, 0.0);
	Up = Vector3D (0.0, 1.0, 0.0);


	RotatedX = RotatedY = RotatedZ = 0.0;
}

void Camera::Move (Vector3D& Direction)
{
	Position = Position + Direction;
}

void Camera::RotateX (GLfloat Angle)
{

	RotatedX += Angle;
	//Rotate viewdir around the right vector:
	View = Vector3D::Normalize(View*cosf(Angle*PIdiv180)+ Up*sinf(Angle*PIdiv180));
	//now compute the new UpVector (by cross product)
	Up = Vector3D::crossProduct(View, Right)*-1;

	
}

void Camera::RotateY (GLfloat Angle)
{
	RotatedY += Angle;
	//Rotate viewdir around the up vector:
	View = Vector3D::Normalize(View*cosf(Angle*PIdiv180)- Right*sinf(Angle*PIdiv180));
	//now compute the new RightVector (by cross product)
	Right = Vector3D::crossProduct(View, Up);
}

void Camera::RotateZ (GLfloat Angle)
{
	RotatedZ += Angle;
	//Rotate viewdir around the right vector:
	Right = Vector3D::Normalize(Right*cosf(Angle*PIdiv180)+ Up*sinf(Angle*PIdiv180));
	//now compute the new UpVector (by cross product)
	Up = Vector3D::crossProduct(View, Right)*-1;
}

void Camera::Render( void )
{
	//calculate view point
	Vector3D ViewPoint = Position+View;

	
	gluLookAt(	Position.getX(),Position.getY(),Position.getZ(),
				ViewPoint.getX(),ViewPoint.getY(),ViewPoint.getZ(),
				Up.getX(),Up.getY(),Up.getZ());

}

void Camera::MoveForward( GLfloat Distance )
{
	Position = Position + (View*Distance);
}

void Camera::MoveRight ( GLfloat Distance )
{
	Position = Position + (Right*Distance);
}

void Camera::MoveUpward( GLfloat Distance )
{
	Position = Position + (Up*Distance);
}

void Camera::SetRotateX(GLfloat Angle)
{
	
	View = Vector3D( 0.0, 0.0, -1.0);
	Right = Vector3D (1.0, 0.0, 0.0);
	Up = Vector3D (0.0, 1.0, 0.0);
	RotatedX=Angle;
}

void Camera::Reset(Vector3D view)
{
	View = view;
	//Position.setVector3D(0, 0, 0);
	Right = Vector3D (1.0, 0.0, 0.0);
	Up = Vector3D (0.0, 1.0, 0.0);
	RotatedX = RotatedY = RotatedZ = 0;
}

Vector3D Camera::getPosition()
{
	return Position;
}

Vector3D Camera::getRotation()
{
	return Vector3D(RotatedX, RotatedY, RotatedZ);
}

Vector3D Camera::getView()
{
	return View;
}