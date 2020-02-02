#pragma once
#include <cmath>
#include "Windows.h"
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Model.h"
#include "MD2Loader.h"
#include "Camera.h"
#include "Polygon3D.h"
#include "AmbientLight.h"


class Rasteriser : public Framework
{
public:
	Rasteriser(); // Default Constructor 
	bool Initialise();
	void Update(const Bitmap &bitmap);
	void Render(const Bitmap &bitmap);
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);
	void AddDirectionLight(COLORREF col, float x, float y, float z);
	void DrawWireFrame(const Bitmap& bitmap);
	void DrawSolidFlat(const Bitmap& bitmap);


	//Accessors
	const std::vector<DirectionLighting>& GetDirectionLights();

	
private:

	Vertex vertices[4];

	Model _model;
	Matrix _PerspectiveProMatrix;
	Matrix _ViewMatrix;
	Matrix TheTransformation;

	Camera _camera{ 0.0f,0.0f,0.0f, Vertex{0.0f,0.0f,-50.0f} };
	float _x{ 1.0f };
	float _y{ 1.0f };
	float _z{ 1.0f };
	int displayMode;
	std::vector<DirectionLighting> _DirectionLights;
	AmbientLight _ambLight;
};