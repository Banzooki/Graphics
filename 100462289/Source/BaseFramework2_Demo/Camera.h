#include "Vertex.h"
#include "Matrix.h"

#pragma once
class Camera // Camera View Class
{
public:
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& posistion);
	void ViewingTransformation();

	// Accessors
	Matrix GetViewing();
	Vertex GetPos();
	

private:
	float _xRotation; // Camera view direction in world space
	float _yRotation;
	float _zRoation;
	Vertex _position; // Camera posistion in world space
	Matrix _ViewingTransformation; // Camera transform matrix
};