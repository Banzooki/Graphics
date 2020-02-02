#pragma once
class Vector3D
{
public:


	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& other);

	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float z);

	Vector3D operator- (const Vector3D& rhs);
	//Vector3D operator= (const Vector3D& rhs);
	void operator = (const Vector3D& rhs);

	static float VectorDotProduct(Vector3D U, Vector3D V);
	static Vector3D VectorCrossProduct(Vector3D U, Vector3D V);


private:
	float _x;
	float _y;
	float _z;
};

