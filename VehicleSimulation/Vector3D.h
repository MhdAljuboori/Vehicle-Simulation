#include<cmath>

#ifndef Vector3D_H
#define Vector3D_H

class Vector3D{

public:
	/////////////// constructors ///////////////////
	Vector3D(): x(0),y(0),z(0) { }
	Vector3D(float newx,  float newy, float newz): x(newx),y(newy),z(newz) { }
	Vector3D(Vector3D& v): x(v.x),y(v.y),z(v.z) { }

	///////////////  setter and getter ////////////
	void setX(float newx) { x=newx; }
	void setY(float newy) { y=newy; }
	void setZ(float newz) { z=newz; }
	void setVector3D(float newx, float newy, float newz) { x=newx; y=newy; z=newz; }

	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	float getLength() { return sqrt( (x*x + y*y + z*z) ); }

	///////////////  Fucntions For Vectors  /////////////////////
	static Vector3D Normalize(Vector3D vect);
	Vector3D getNormalize();
	Vector3D loadZero();
	Vector3D loadOne();

	bool isInSameDirection(Vector3D&);

	//////////////  Mathematical Operations  //////////////
	Vector3D Add(Vector3D&);
	Vector3D Substract(Vector3D&);
	static Vector3D crossProduct(Vector3D&, Vector3D&);
	float dotProduct(Vector3D&);


	//////////// Overloaded Operators //////////////
	Vector3D operator=(Vector3D&);
	Vector3D operator+(Vector3D&);
	Vector3D operator-(Vector3D&);
	Vector3D operator*(Vector3D&);
	Vector3D operator/(Vector3D&);
	//Vector3D operator^(Vector3D&);

	Vector3D operator=(float);
	Vector3D operator+(float);
	Vector3D operator-(float);
	Vector3D operator*(float);
	Vector3D operator/(float);

	friend Vector3D operator+(float,Vector3D&);
	friend Vector3D operator-(float,Vector3D&);
	friend Vector3D operator*(float,Vector3D&);
	friend Vector3D operator/(float,Vector3D&);

	bool operator==(Vector3D&);
	bool operator!=(Vector3D&);

	void operator-=(float);
	void operator+=(float);
	void operator*=(float);
	void operator/=(float);

	void operator-=(Vector3D&);
	void operator+=(Vector3D&);
	void operator*=(Vector3D&);
	void operator/=(Vector3D&);


	/////////////  Class Data  Members  //////////////
private:
	float x;
	float y;
	float z;


};

#endif
