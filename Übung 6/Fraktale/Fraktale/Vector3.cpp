#include "pch.h"
#include "Vector3.h"

Vector3::Vector3()
{
	for (int i = 0; i < DIM; i++)
		vek[i] = 0;
	vek[DIM - 1] = 1;
}

Vector3::Vector3(double x, double y, double z)
{
	vek[0] = x;
	vek[1] = y;
	vek[2] = z;
	vek[3] = 1;
}

Vector3::~Vector3()
{

}

Vector3 Vector3::operator *(double s)
{
	Vector3 temp;
	for (int i = 0; i < DIM; i++)
		temp.vek[i] = vek[i] * s;
	return temp;
}

Matrix3::Matrix3()
{
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			if (i == j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
}
Vector3 Matrix3::operator *(const Vector3& v)
{
	Vector3 temp;
	for (int i = 0; i < DIM; i++)
	{
		temp.vek[i] = 0;
		for (int j = 0; j < DIM; j++)
		{
			temp.vek[i] += mat[i][j] * v.vek[j];
		}
	}
	return temp;
}

Matrix3 Matrix3::operator*(const Matrix3& m)
{
	Matrix3 temp;
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			temp.mat[i][j] = 0;
			for (int k = 0; k < DIM; k++)
			{
				temp.mat[i][j] += mat[i][k] * m.mat[k][j];
			}
		}
	}
	return temp;
}

Matrix3::~Matrix3()
{

}


void Matrix3::setTrans(double x, double y, double z)
{
	mat[0][3] = x;
	mat[1][3] = y;
	mat[2][3] = z;
}


void Matrix3::setRotZ(double w)
{
	mat[0][0] = mat[1][1] = cos(w);
	mat[0][1] = sin(w);
	mat[1][0] = -sin(w);
}

void Matrix3::setRotX(double w)
{
	mat[1][1] = mat[2][2] = cos(w);
	mat[1][2] = sin(w);
	mat[2][1] = -sin(w);
}

int Matrix3::setPersp(double dist)
{
	mat[2][2] = 0;
	mat[3][2] = 1. / dist;
	return 0;
}

