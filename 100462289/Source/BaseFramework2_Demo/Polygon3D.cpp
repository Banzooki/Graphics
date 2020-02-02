#include "Polygon3D.h"

Polygon3D::Polygon3D() :_indices{ 0 } // Default Constructor
{

}

Polygon3D::Polygon3D(int index0, int index1, int index2, COLORREF theColour) // Constructor using index vertices and the colour
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_colour = theColour;
	see = true;
	AverageZ = 0;
}

Polygon3D::~Polygon3D()// Destructor
{

}

Polygon3D::Polygon3D(const Polygon3D& p) //Constructor from a reference
{
	_indices[0] = p.GetIndex(0);
	_indices[1] = p.GetIndex(1);
	_indices[2] = p.GetIndex(2);
	see = p.Getsee();
	AverageZ = p.GetAVG();
	_colour = p.getColour();
}
//Accsessors
int Polygon3D::GetIndex(int number) const
{
	return _indices[number];
}

bool Polygon3D::Getsee() const
{
	return see;
}

float Polygon3D::GetAVG() const
{
	return AverageZ;
}

COLORREF Polygon3D::getColour() const
{
	return _colour;
}

Vector3D Polygon3D::Getnormal() const
{
	return normal;
}

//Mutators
void Polygon3D::Setsee(bool c)
{
	see = c;
}

void Polygon3D::SetAVG(float avgZ)
{
	AverageZ = avgZ;
}

void Polygon3D::setColour(COLORREF myColour)
{
	_colour = myColour;
}

void Polygon3D::Setnormal(Vector3D _normal)
{
	normal = _normal;
}

//Operator Overrides
void Polygon3D::operator=(const Polygon3D& rhs)
{
	_indices[0] = rhs.GetIndex(0);
	_indices[1] = rhs.GetIndex(1);
	_indices[2] = rhs.GetIndex(2);
	_colour = rhs.getColour();

	see = rhs.see;
	AverageZ = rhs.AverageZ;
	normal = rhs.normal;
}
