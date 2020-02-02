#include "Vector3D.h"

Vector3D::Vector3D() // Default Constructor
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
}

Vector3D::Vector3D(float x, float y, float z) //constructor from direction
{
	_x = x;
	_y = y;
	_z = z;
}

Vector3D::Vector3D(const Vector3D& other) //constructor from a reference
{
	_x = other.GetX();
	_y = other.GetY();
	_z = other.GetZ();
}

//Accessors
float Vector3D::GetX() const
{
	return _x;
}

float Vector3D::GetY() const
{
	return _y;
}

float Vector3D::GetZ() const
{
	return _z;
}

//Mutators
void Vector3D::SetX(const float x)
{
	_x = x;
}

void Vector3D::SetY(const float y)
{
	_y = y;
}

void Vector3D::SetZ(const float z)
{
	_z = z;
}

//Operator Overrides
Vector3D Vector3D::operator-(const Vector3D& rhs)
{
	return Vector3D(_x - rhs.GetX(), _y - rhs.GetY(), _z - rhs.GetZ());
}

void Vector3D::operator=(const Vector3D& rhs)
{
	_x = rhs.GetX();
	_y = rhs.GetY();
	_z = rhs.GetZ();
}

// Vector Calculatations
float Vector3D::VectorDotProduct(Vector3D U,Vector3D V)
{
	return float (U.GetX() * V.GetX() + U.GetY() * V.GetY() + U.GetZ() * V.GetZ());
}

Vector3D Vector3D::VectorCrossProduct(Vector3D U, Vector3D V)
{
	return Vector3D(U.GetY() * V.GetZ() - U.GetZ() * V.GetY(),
					U.GetZ() * V.GetX() - U.GetX() * V.GetZ(),
					U.GetX() * V.GetY() - U.GetY() * V.GetX());
}