#include "Rasteriser.h"

Rasteriser app;


Rasteriser::Rasteriser() // Default Constructor
{
	displayMode = 0;
}

bool Rasteriser::Initialise() // creates the model
{
	_ambLight.SetColour(RGB(8, 19, 32)); // Dark Blue Ambient Light
	AddDirectionLight(RGB(32, 0, 0), 2, 3, 1); // Adds a direction light of red colour

	if (!MD2Loader::LoadModel("marvin.md2", _model, // loads the data model
		&Model::AddPolygon,
		&Model::AddVertex))
	{
		return false;
	}
	return true;
}

void Rasteriser::Update(const Bitmap& bitmap) // Generate a frame
{
	//Change though animations
	switch (displayMode)
	{
		case 0: // Rotation around Y
		case 6:
		case 7:
		case 8:
		case 9:
		{
			float radians = static_cast<float>(_y * 3.14 / 180);

			Matrix rotation = {
				cos(radians),0,sin(radians),0,
				0,1,0,0,
				-sin(radians),0,cos(radians),0,
				0,0,0,1
			};

			if (_y != 360)
			{
				_y += 1;
				_x += 1;
				_z += 1;
			}
			else
			{
				_y = 0;
				displayMode++;
			}

			TheTransformation = rotation;
		}
			break;

		case 1: // Rotation around X
		{
			float radians = static_cast<float>(_y * 3.14 / 180);

			Matrix rotation = {
				1,0,0,0,
				0,cos(radians),-sin(radians),0,
				0, sin(radians),cos(radians),0,
				0,0,0,1
			};

			if (_y != 360)
			{
				_y += 1;
			}
			else
			{
				_y = 0;
				displayMode++;
			}

			TheTransformation = rotation;
	}
	break;

		case 2: // Rotation around Z
		{
			float radians = static_cast<float>(_y * 3.14 / 180);

			Matrix rotation = {
				cos(radians),-sin(radians),0,0,
				sin(radians),cos(radians),0,0,
				0,0,1,0,
				0,0,0,1
			};

			if (_y != 360)
			{
				_y += 1;
			}
			else
			{
				_y = 0;
				displayMode++;
			}

			TheTransformation = rotation;
		}
		break;

		case 3: // Scaling
		{
			Matrix scale = {
				_y,0,0,0,
				0,_y,0,0,
				0,0,_y,0,
				0,0,0,1
			};

			if (_y < 2.0f)
				_y += 0.005f;
			else
			{
				_y = 1.0f;
				displayMode++;
			}

			TheTransformation = scale;
		}
			break;

		case 4: // Translate up
		{
			Matrix translaion = {
				1,0,0,1,
				0,1,0,_y,
				0,0,1,1,
				0,0,0,1
			};
			if (_y < 10)
				_y += 0.05f;
			else
			{
				_y = 1.0f;
				displayMode++;
			}

			TheTransformation = translaion;
		}
			break;

		case 5: // Translate right
		{
			Matrix translaion = {
				1,0,0,_y,
				0,1,0,1,
				0,0,1,1,
				0,0,0,1
			};
			if (_y < 10)
				_y += 0.05f;
			else
			{
				_y = 1.0f;
				displayMode++;
			}

			TheTransformation = translaion;
		}
		break;


		default:
			break;
	}
	
	GeneratePerspectiveMatrix(1.0f, float(bitmap.GetWidth()) / float(bitmap.GetHeight())); // Method call for the perspective matrix

	GenerateViewMatrix(1.0f, bitmap.GetWidth(), bitmap.GetHeight()); // Method call for the view matrix
}

void Rasteriser::Render(const Bitmap& bitmap) // Draw a frame
{
	bitmap.Clear(RGB(255, 255, 255)); // clears the bitmap

	_model.ApplyTransformToLocalVertices(TheTransformation); // Method call for the current transformation matrix

	// Generating the model based on current animation mode
	switch (displayMode)
	{
		case 0:		// Wireframe modes
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			_model.ApplyTransformToTransformedVertices(_camera.GetViewing());
			_model.ApplyTransformToTransformedVertices(_PerspectiveProMatrix);
			_model.DehomogeniseTransformVertices();
			_model.ApplyTransformToTransformedVertices(_ViewMatrix);
			DrawWireFrame(bitmap);
			break;

		case 6:	// Wireframe with culling modes
			_model.CalculateBackfaces(_camera.GetPos());
			_model.ApplyTransformToTransformedVertices(_camera.GetViewing());
			_model.ApplyTransformToTransformedVertices(_PerspectiveProMatrix);
			_model.DehomogeniseTransformVertices();
			_model.ApplyTransformToTransformedVertices(_ViewMatrix);
			DrawWireFrame(bitmap);
			break;

		case 7: // Wireframe with culling and Z depth sorting
			_model.CalculateBackfaces(_camera.GetPos());
			_model.ApplyTransformToTransformedVertices(_camera.GetViewing());
			_model.Sort();
			_model.ApplyTransformToTransformedVertices(_PerspectiveProMatrix);
			_model.DehomogeniseTransformVertices();
			_model.ApplyTransformToTransformedVertices(_ViewMatrix);
			DrawWireFrame(bitmap);
			break;

		case 8: // Flat shading
			_model.CalculateBackfaces(_camera.GetPos());
			_model.ApplyTransformToTransformedVertices(_camera.GetViewing());
			_model.Sort();
			_model.ApplyTransformToTransformedVertices(_PerspectiveProMatrix);
			_model.DehomogeniseTransformVertices();
			_model.ApplyTransformToTransformedVertices(_ViewMatrix);
			DrawSolidFlat(bitmap);
			break;

		case 9:	// Directional lighting
			_model.CalculateBackfaces(_camera.GetPos());
			_model.CalculateLightingDirectional(_ambLight, GetDirectionLights());
			_model.ApplyTransformToTransformedVertices(_camera.GetViewing());
			_model.Sort();
			_model.ApplyTransformToTransformedVertices(_PerspectiveProMatrix);
			_model.DehomogeniseTransformVertices();
			_model.ApplyTransformToTransformedVertices(_ViewMatrix);
			DrawSolidFlat(bitmap);
			break;

		default:
			break;
	}
}

//Matrices for view transformation
void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	_PerspectiveProMatrix = {
		d / aspectRatio,0,0,0,
		0,d,0,0,
		0,0,d,0,
		0,0,1,0
	};
}

void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	_ViewMatrix = {
		width / 2.0f,0,0,width / 2.0f,
		0,-height / 2.0f,0,height / 2.0f,
		0,0,d / 2,d / 2,
		0,0,0,1
	};
}

//Draws the wireframe of the model
void Rasteriser::DrawWireFrame(const Bitmap& bitmap)
{
	for (const Polygon3D& polygon : _model.GetPolygons())
	{
		if (polygon.Getsee())
		{
			Vertex tri1 = _model.GetTransVertices()[polygon.GetIndex(0)];
			Vertex tri2 = _model.GetTransVertices()[polygon.GetIndex(1)];
			Vertex tri3 = _model.GetTransVertices()[polygon.GetIndex(2)];
			MoveToEx(bitmap.GetDC(), int(tri1.GetX()), int(tri1.GetY()), NULL);
			LineTo(bitmap.GetDC(), int(tri2.GetX()), int(tri2.GetY()));
			LineTo(bitmap.GetDC(), int(tri3.GetX()), int(tri3.GetY()));
			LineTo(bitmap.GetDC(), int(tri1.GetX()), int(tri1.GetY()));

			//Displays text descriptiopn based on current animation
			switch (displayMode)
			{
			case 0:
				TextOut(bitmap.GetDC(), 5, 5, TEXT("Wireframe Y Rotation"), 20);
				break;
			case 1:
				TextOut(bitmap.GetDC(), 5, 5, TEXT("Wireframe X Rotation"), 20);
				break;
			case 2:
				TextOut(bitmap.GetDC(), 5, 5, TEXT("Wireframe Z Rotation"), 20);
				break;
			case 3:
				TextOut(bitmap.GetDC(), 5, 5, TEXT("Wireframe Scaling"), 17);
				break;
			case 4:
				TextOut(bitmap.GetDC(), 5, 5, TEXT("Wireframe Translate Up"), 22);
				break;
			case 5:
				TextOut(bitmap.GetDC(), 5, 5, TEXT("Wireframe Translate Right"), 25);
				break;
			case 6:
				TextOut(bitmap.GetDC(), 5, 5, TEXT("Wireframe + Backface"), 20);
				break;
			case 7:
				TextOut(bitmap.GetDC(), 5, 5, TEXT("Wireframe + Backface + Z Depth Sorting"), 38);
				break;
			}
		}
	}
}

//Draw the solid shading views
void Rasteriser::DrawSolidFlat(const Bitmap& bitmap)
{
	for (const Polygon3D& polygon : _model.GetPolygons())
	{
		if (polygon.Getsee())
		{
			Vertex tri1 = _model.GetTransVertices()[polygon.GetIndex(0)];
			Vertex tri2 = _model.GetTransVertices()[polygon.GetIndex(1)];
			Vertex tri3 = _model.GetTransVertices()[polygon.GetIndex(2)];
			
			POINT a{ (LONG)tri1.GetX(), (LONG)tri1.GetY() };
			POINT b{ (LONG)tri2.GetX(), (LONG)tri2.GetY() };
			POINT c{ (LONG)tri3.GetX(), (LONG)tri3.GetY() };

			POINT poly[3]
			{
				a, b, c
			};

			HBRUSH owobrush = CreateSolidBrush(polygon.getColour());
			HBRUSH brushyhead = (HBRUSH)SelectObject(bitmap.GetDC(), owobrush);

			HPEN owopen = CreatePen(PS_NULL, 1, polygon.getColour());
			HPEN pennyhead = (HPEN)SelectObject(bitmap.GetDC(), owopen);

			Polygon(bitmap.GetDC(), poly, 3);

			SelectObject(bitmap.GetDC(), brushyhead);
			DeleteObject(owobrush);

			SelectObject(bitmap.GetDC(), pennyhead);
			DeleteObject(owopen);

			//Displays text descriptiopn based on current animation
			switch (displayMode)
			{
			case 8:
				TextOut(bitmap.GetDC(), 5, 5, TEXT("Solidflat Shading"), 17);
				break;
			case 9:
				TextOut(bitmap.GetDC(), 5, 5, TEXT("Solidflat Shading + Directional Light"), 37);
				break;
			}
		}
	}
}


const std::vector<DirectionLighting>& Rasteriser::GetDirectionLights() //Accessor
{
	return _DirectionLights;
}

void Rasteriser::AddDirectionLight(COLORREF col, float x, float y, float z)//Adds a direction light to the collection of direction lights
{
	_DirectionLights.push_back(DirectionLighting(col, x, y, z));
}