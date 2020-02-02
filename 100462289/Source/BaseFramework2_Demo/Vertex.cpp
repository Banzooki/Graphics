#include "Vertex.h"

Vertex::Vertex() // Default Constructor
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_w = 1;
}

Vertex::Vertex(float x, float y,float z) //Constructor from posistion
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1;
}

Vertex::Vertex(const Vertex& other) // constructor from a reference
{
	_x = other.GetX();
	_y = other.GetY();
	_z = other.GetZ();
	_w = other.GetW();
}

//Accessors
float Vertex::GetX() const
{
	return _x;
}

float Vertex::GetY() const
{
	return _y;
}

float Vertex::GetZ() const
{
	return _z;
}

float Vertex::GetW() const
{
	return _w;
}

//Mutators
void Vertex::SetX(const float x)
{
	_x = x;
}

void Vertex::SetY(const float y)
{
	_y = y;
}

void Vertex::SetZ(const float z)
{
	_z = z;
}

void Vertex::SetW(const float w)
{
	_w = w;
}

//operator overrides
Vertex& Vertex::operator=(const Vertex& rhs)
{
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
		_w = rhs.GetW();
	}
	return *this;
}

bool Vertex::operator==(const Vertex& rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ() && _w == rhs.GetW());
}

const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
}

const Vector3D Vertex::operator-(const Vertex& rhs) const
{
	return Vector3D(_x - rhs.GetX(), _y - rhs.GetY(), _z - rhs.GetZ());
}

// Dehomgenise the posistion
void Vertex::Dehomogenise()
{	
	_x /= _w;
	_y /= _w;
	_z /= _w;
	_w /= _w;
}