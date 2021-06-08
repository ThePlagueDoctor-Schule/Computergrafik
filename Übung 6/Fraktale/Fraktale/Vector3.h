#pragma once
#define DIM 4
class Vector3
{
public:
	double vek[DIM];
	Vector3();
	Vector3(double x, double y, double z);
	~Vector3();
	Vector3 operator *(double s);
	double getHom() { return vek[3]; }
};

class Matrix3
{
	double mat[DIM][DIM];
public:
	Matrix3();
	Vector3 operator *(const Vector3& v);
	Matrix3 operator *(const Matrix3& m);
	~Matrix3();
	void setTrans(double x, double y, double z);
	void setRotZ(double w);
	void setRotX(double w);
	int setPersp(double dist);
};

