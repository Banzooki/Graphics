#pragma once
#include <Windows.h>

class AmbientLight
{
public:
	AmbientLight();
	AmbientLight(COLORREF theColour);

	//Accessor
	COLORREF GetColour() const;
	//Mutator
	void SetColour(const COLORREF newColour);

private:
	COLORREF col; // Ambient Light Colour
};

