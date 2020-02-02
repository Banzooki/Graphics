#include "Model.h"
#include <algorithm>

bool UDgreater(Polygon3D& polygon0, Polygon3D& polygon1)// Predigate for the Z sort function
{
	return polygon0.GetAVG() > polygon1.GetAVG();
}

Model::Model() // Default Constructor
{
	kd_red = 1.0f;
	kd_green = 1.0f;
	kd_blue = 1.0f;
}

Model::~Model() // Destructor
{
}
//Accsessors
const std::vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

const std::vector<Vertex>& Model::GetVertices()
{
	return _vertices;
}

const std::vector<Vertex>& Model::GetTransVertices()
{
	return _transVertices;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetVertexCount() const
{
	return _vertices.size();
}

size_t Model::GetTransVertexCount() const
{
	return _transVertices.size();
}
//Data Builders
void Model::AddVertex(float x, float y, float z) 
{
	_vertices.push_back(Vertex(x, y, z));
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2));
}

//View and sort calculatations
void Model::DehomogeniseTransformVertices()
{
	for (int i = 0; i < GetTransVertexCount(); i++)
	{
		_transVertices[i].Dehomogenise();
	}
}

void Model::ApplyTransformToLocalVertices(const Matrix& transform)
{
	_transVertices.clear();

	for (size_t i = 0; i < GetVertexCount(); i++)
	{
		_transVertices.push_back(transform * _vertices[i]);
	}
}

void Model::ApplyTransformToTransformedVertices(const Matrix& transform)
{
	for (size_t i = 0; i < GetTransVertexCount(); i++)
	{
		_transVertices[i] = transform * _transVertices[i];
	}
}

void Model::CalculateBackfaces(const Vertex& cameraPosition)
{
	for (Polygon3D& Poly1 : _polygons)
	{
		int index0 = Poly1.GetIndex(0);
		int index1 = Poly1.GetIndex(1);
		int index2 = Poly1.GetIndex(2);
			   
		Vertex Vertex0 = _transVertices[index0];
		Vertex Vertex1 = _transVertices[index1];
		Vertex Vertex2 = _transVertices[index2];

		Vector3D a = Vertex0 - Vertex1;
		Vector3D b = Vertex0 - Vertex2;
		Vector3D normal =Vector3D::VectorCrossProduct(b, a);
		Poly1.Setnormal(normal);

		Vector3D eyeVector = Vertex0 - cameraPosition;

		float backFace = Vector3D::VectorDotProduct(normal, eyeVector);
		if (backFace < 0)
		{
			Poly1.Setsee(false);
		}
		else
		{
			Poly1.Setsee(true);
		}
	}
}

void Model::Sort()
{
	for (Polygon3D& Poly2 : _polygons)
	{
		Vertex Vertex0 = _transVertices[Poly2.GetIndex(0)];
		Vertex Vertex1 = _transVertices[Poly2.GetIndex(1)];
		Vertex Vertex2 = _transVertices[Poly2.GetIndex(2)];

		Poly2.SetAVG((Vertex0.GetZ() + Vertex1.GetZ() + Vertex2.GetZ()) / 3.0f);
	}

	sort(_polygons.begin(), _polygons.end(), UDgreater);
}

void Model::CalculateLightingDirectional(AmbientLight ambLight, std::vector<DirectionLighting> DirectionLights)
{
	float tempR = 0.0f;
	float tempG = 0.0f;
	float tempB = 0.0f;

	for (Polygon3D& poly3 : _polygons)
	{
		float totalR = GetRValue(ambLight.GetColour());
		float totalG = GetGValue(ambLight.GetColour());
		float totalB = GetBValue(ambLight.GetColour());

		for (DirectionLighting Light1 : DirectionLights)
		{
			tempR = Light1.GetR();
			tempG = Light1.GetG();
			tempB = Light1.GetB();

			tempR *= kd_red;
			tempG *= kd_green;
			tempB *= kd_blue;

			Vector3D normal = poly3.Getnormal();
			float LightDot = Vector3D::VectorDotProduct(Light1.GetLightVector(), normal);

			tempR *= LightDot;
			tempG *= LightDot;
			tempB *= LightDot;

			totalR += tempR;
			totalG += tempG;
			totalB += tempB;
		}

		if (totalR < 0) totalR = 0; else if (totalR > 255) totalR = 255;
		if (totalG < 0) totalG = 0; else if (totalG > 255) totalG = 255;
		if (totalB < 0) totalB = 0; else if (totalB > 255) totalB = 255;

		poly3.setColour(RGB(totalR, totalG, totalB));
	}
}
