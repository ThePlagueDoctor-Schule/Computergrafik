#pragma once
#define DIM 3
class Vector2
{
public:
	double vek[DIM];
	Vector2();
	Vector2(double x, double y);
	~Vector2();
};

class Matrix2
{
	double mat[DIM][DIM];
public:
	Matrix2();
	Vector2 operator *(const Vector2& v);
	Matrix2 operator *(const Matrix2& m);
	~Matrix2();
	void setTrans(double x, double y);
	void setRot(double w);
};

