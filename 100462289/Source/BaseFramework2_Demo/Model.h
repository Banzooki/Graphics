#pragma once
#include <vector>
#include "Vector3D.h"
#include "Vertex.h"
#include "Polygon3D.h"
#include "Matrix.h"
#include "DirectionLighting.h"
#include "AmbientLight.h"

class Model
{
public:
	Model(); // Default construtor
	~Model(); //Defai;t destructor



	//Accessors
	const std::vector<Polygon3D>& GetPolygons();
	const std::vector<Vertex>& GetVertices();
	const std::vector <Vertex>& GetTransVertices();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	size_t GetTransVertexCount() const;

	// Data Builders
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);

	// Drawing Transformations
	void DehomogeniseTransformVertices();
	void ApplyTransformToLocalVertices(const Matrix& transform);
	void ApplyTransformToTransformedVertices(const Matrix& transform);
	void CalculateBackfaces(const Vertex& posistion);
	void Sort(void);
	void CalculateLightingDirectional(AmbientLight ambLight, std::vector<DirectionLighting> DirectionLights);

private:
	std::vector<Polygon3D>	_polygons; // Polygon Data
	std::vector<Vertex>		_vertices; // Vertex Data
	std::vector<Vertex> _transVertices; //Transformed Vertex Data


	float kd_red; // Reflection Coefficients
	float kd_green;
	float kd_blue;

};

