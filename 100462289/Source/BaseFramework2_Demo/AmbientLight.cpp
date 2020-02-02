#include "AmbientLight.h"

AmbientLight::AmbientLight() // Default constructor
{
	col = RGB(0,0,0);
}

AmbientLight::AmbientLight(COLORREF theColour) // Constructor using colour
{
	col = theColour;
}

COLORREF AmbientLight::GetColour() const // Accsessor for getting the colour
{
	return col;
}

void AmbientLight::SetColour(const COLORREF newColour) // Mutator to set the colour
{
	col = newColour;
}
