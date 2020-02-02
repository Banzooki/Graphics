#pragma once
#include "Model.h"

typedef void (Model::* AddVertex)(float x, float y, float z);
typedef void (Model::* AddPolygon)(int i0, int i1, int i2);

class MD2Loader // Model Data Loader
{
public:
	static bool LoadModel(const char* md2Filename, Model& model, AddPolygon addPolygon, AddVertex addVertex);
};
