#include "Camera.h"
#include <cmath>

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& posistion) // camera constructor with the direction and position
{
	_xRotation = xRotation;
	_yRotation = yRotation;
	_zRoation = zRotation;
	_position = posistion;
	ViewingTransformation();
}

float ConvertDeg(float deg) // A function to converted degrees into Radians
{
	return float (deg * 3.14) / 180;
}

void Camera::ViewingTransformation() // Calculates the view transformation matrix
{
	Matrix X
	{
		1,0,0,0,
		0, cos(ConvertDeg(_xRotation)),sin(ConvertDeg(_xRotation)),0,
		0, -sin(ConvertDeg(_xRotation)),cos(ConvertDeg(_xRotation)),0,
		0,0,0,1
	};

	Matrix Y
	{
		cos(ConvertDeg(_yRotation)),0,-sin(ConvertDeg(_yRotation)),0,
		0,1,0,0,
		sin(ConvertDeg(_yRotation)),0,cos(ConvertDeg(_yRotation)),0,
		0,0,0,1
	};

	Matrix Z
	{
		cos(ConvertDeg(_zRoation)),sin(ConvertDeg(_zRoation)),0,0,
		-sin(ConvertDeg(_zRoation)),cos(ConvertDeg(_zRoation)),0,0,
		0,0,1,0,
		0,0,0,1,
	};

	Matrix Dave
	{
		1,0,0,-_position.GetX(),
		0,1,0,-_position.GetY(),
		0,0,1,-_position.GetZ(),
		0,0,0,1
	};

	_ViewingTransformation = X * Y * Z * Dave;
}

Matrix Camera::GetViewing() // Accsessor to get the viewing transformation matrix
{
	return _ViewingTransformation;
}

Vertex Camera::GetPos() // Mutator to set the transformation matrix
{
	return _position;
}