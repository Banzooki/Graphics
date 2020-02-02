#include "DirectionLighting.h"
#include <cmath>

DirectionLighting::DirectionLighting() // Default Constructor
{
	_col = 0;
}

DirectionLighting::~DirectionLighting() // Destructor
{

}

DirectionLighting::DirectionLighting(COLORREF col, float x, float y, float z) // Constructor using the colour and posistion of the directional light
{
	_col = col;
	float Length = sqrt(x * x + y * y + z * z); //calculate length of vector

	_Direction.SetX(x / Length);	// set normalised components
	_Direction.SetY(y / Length);
	_Direction.SetZ(z / Length);
}

Vector3D DirectionLighting::GetLightVector() // Accessor for the Light Vector
{
	return _Direction;
}
// Accsessor for colour components
float DirectionLighting::GetR() const
{
	return (float)GetRValue(_col);
}

float DirectionLighting::GetG() const
{
	return (float)GetGValue(_col);
}

float DirectionLighting::GetB() const
{
	return (float)GetBValue(_col);
}
