#pragma once
#include <Windows.h>
#include "Vector3D.h"
class Polygon3D
{
public:
	Polygon3D(); //Default Constructor
	Polygon3D(int index0, int index1, int index2, COLORREF _colour=RGB(0,0,0)); // Polygon Constructor
	Polygon3D(const Polygon3D& p); // Polygon Constructor from reference
	~Polygon3D(); //Destructor

	//Accessor
	int GetIndex(int) const;
	bool Getsee() const;
	float GetAVG() const;
	COLORREF getColour() const;
	Vector3D Getnormal() const;

	// Mutators
	void Setsee(bool c);
	void SetAVG(float AVG);
	void setColour(COLORREF myColour);
	void Setnormal(Vector3D _normal);

	//Operator Overrides
	void operator= (const Polygon3D& rhs);

private:
	int _indices[3]; //Polygon vertex indices
	bool see; // Wether culled
	float AverageZ; // Avergae Z for depth sorting
	COLORREF _colour; // Colour for solid shading
	Vector3D normal; // Calculated normal value of a polygon
};