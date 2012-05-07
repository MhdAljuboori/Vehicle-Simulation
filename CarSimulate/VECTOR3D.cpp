#include"VECTOR3D.h"

#include<cmath>

////////////////  Functions For Vectors  //////////////
void Vector3D::Normalize()
{
	float length=getLength();
	if(length == 1 || length == 0)
		return ;
	x/=length;
	y/=length;
	z/=length;
}

Vector3D Vector3D::getNormalize()
{
	Vector3D normalize;
	normalize.x=this->x/getLength();
	normalize.y=this->y/getLength();
	normalize.z=this->z/getLength();
	return normalize;
}

Vector3D Vector3D::loadZero()
{
	return Vector3D(0,0,0);

}

Vector3D Vector3D::loadOne()
{
	return Vector3D(1,1,1);
}

bool Vector3D::isInSameDirection(Vector3D& vector)
{
	if( this->dotProduct(vector) > 0 )
		return true;
	else
		return false;
}

///////////////  Mathmathical  Operations ////////////
Vector3D Vector3D::Add(Vector3D& vector)
{
	return Vector3D(this->x + vector.x ,this->y + vector.y ,this->z + vector.z);
}

Vector3D Vector3D::Substract(Vector3D& vector)
{
	return Vector3D(this->x - vector.x ,this->y - vector.y ,this->z - vector.z);
}

Vector3D Vector3D::crossProduct(Vector3D& vector)
{
	return Vector3D( (this->y*vector.z)- (this->z*vector.y) , (this->z*vector.x) - (this->x*vector.z) , (this->x*vector.y) - (this->y*vector.x) );
}

float Vector3D::dotProduct(Vector3D& vector)
{
	return ( this->x*vector.x + this->y*vector.y + this->z*vector.z );
}


/////////////  Overloaded  Operators   //////////////

Vector3D Vector3D::operator=(Vector3D& vector)
{
	this->x =vector.x ;  this->y=vector.y ; this->z = vector.z;
	return *this;
	//return Vector3D(vector.x,vector.y,vector.z);
}

Vector3D Vector3D::operator+(Vector3D& vector)
{
	return Vector3D(this->x + vector.x ,this->y + vector.y ,this->z + vector.z);
}

Vector3D Vector3D::operator-(Vector3D& vector)
{
	return Vector3D(this->x - vector.x ,this->y - vector.y ,this->z - vector.z);
}

Vector3D Vector3D::operator*(Vector3D& vector)
{
	return Vector3D(this->x * vector.x ,this->y * vector.y ,this->z * vector.z);
}

Vector3D Vector3D::operator/(Vector3D& vector)
{
	return Vector3D(this->x / vector.x ,this->y / vector.y ,this->z / vector.z);
}

//////////////////////////////////////////////
//////////////////////////////////////////////

bool Vector3D::operator==(Vector3D& vector)
{
	if(this->x == vector.x && this->y == vector.y && this->z == vector.z)
		return true;
	else
		return false;
}

bool Vector3D::operator!=(Vector3D& vector)
{
	if(this->x != vector.x || this->y != vector.y || this->z != vector.z)
		return true;
	else
		return false;
}

////////////////////////////////////////////////
////////////////////////////////////////////////
/////// v1+=2;

void Vector3D::operator+=(float scale)
{
	this->x = this->x + scale ;
	this->y = this->y + scale ;
	this->z = this->z + scale ;
}

void Vector3D::operator-=(float scale)
{
	this->x = this->x - scale ;
	this->y = this->y - scale ;
	this->z = this->z - scale ;
}

void Vector3D::operator*=(float scale)
{
	this->x = this->x * scale ;
	this->y = this->y * scale ;
	this->z = this->z * scale ;
}

void Vector3D::operator/=(float scale)
{
	if(scale == 0)
		return ;
	else
	{
		this->x = this->x / scale ;
		this->y = this->y / scale ;
		this->z = this->z / scale ;
	}
}


/////// v1 = v2 + 3; /////////////////

Vector3D Vector3D::operator+(float scale)
{
	return Vector3D(this->x + scale,this->y + scale,this->z + scale);
}

Vector3D Vector3D::operator-(float scale)
{
	return Vector3D(this->x - scale,this->y - scale,this->z - scale);
}

Vector3D Vector3D::operator*(float scale)
{
	return Vector3D(this->x * scale,this->y * scale,this->z * scale);
}

Vector3D Vector3D::operator/(float scale)
{
	if(scale == 0)
		return Vector3D(0,0,0);
	else
		return Vector3D(this->x / scale,this->y / scale,this->z / scale);
}


/// v1= 2 + v2 ;

Vector3D operator+(float scale,Vector3D& v)
{
	return Vector3D(v.x + scale ,v.y + scale ,v.z + scale);
}

Vector3D operator-(float scale,Vector3D& v)
{
	return Vector3D(scale - v.x  ,scale - v.y ,scale - v.z);
}

Vector3D operator*(float scale,Vector3D& v)
{
	return Vector3D(v.x*scale ,v.y*scale ,v.z*scale);
}

Vector3D operator/(float scale,Vector3D& v)
{
	if(scale == 0)
		return Vector3D(0,0,0);
	else
		return Vector3D(scale /v.x  ,scale / v.y ,scale /v.z);
}

///////// v1+= v2; 
void Vector3D::operator+=(Vector3D& vector)
{
	this->x = this->x + vector.x ;
	this->y = this->y + vector.y ;
	this->z = this->z + vector.z ;
}

void Vector3D::operator-=(Vector3D& vector)
{
	this->x = this->x - vector.x ;
	this->y = this->y - vector.y ;
	this->z = this->z - vector.z ;
}

void Vector3D::operator*=(Vector3D& vector)
{
	this->x = this->x * vector.x ;
	this->y = this->y * vector.y ;
	this->z = this->z * vector.z ;
}

void Vector3D::operator/=(Vector3D& vector)
{
	this->x = this->x / vector.x ;
	this->y = this->y / vector.y ;
	this->z = this->z / vector.z ;
}

////////////////////////////////////////////////////////
////////////////////////////////////
/////////////////////////////
////////////////////////
///////////////////
/////////////
