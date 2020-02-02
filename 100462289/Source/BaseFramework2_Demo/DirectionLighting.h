#pragma once
#include <Windows.h>
#include "Vector3D.h"

class DirectionLighting // Direction Light Class
{
public:
	DirectionLighting();
	~DirectionLighting();
	DirectionLighting(COLORREF col, float x, float y, float z);

	// Accessors
	Vector3D GetLightVector();
	float GetR() const;
	float GetG() const;
	float GetB() const;

private:
	COLORREF _col; // Direction Light Colour
	Vector3D _Direction; // Direction Light Direction
};

