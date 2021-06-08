#include "pch.h"
#include "Vector2.h"

Vector2::Vector2()
{
	for (int i = 0; i < DIM; i++)
		vek[i] = 0;
	vek[DIM - 1] = 1;
}

Vector2::Vector2(double x, double y)
{
	vek[0] = x;
	vek[1] = y;
	vek[2] = 1;
}

Vector2::~Vector2()
{

}

Matrix2::Matrix2()
{
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			if (i == j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
}
Vector2 Matrix2::operator *(const Vector2& v)
{
	Vector2 temp;
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

Matrix2 Matrix2::operator*(const Matrix2& m)
{
	Matrix2 temp;
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

Matrix2::~Matrix2()
{

}


void Matrix2::setTrans(double x, double y)
{
	mat[0][2] = x;
	mat[1][2] = y;
}


void Matrix2::setRot(double w)
{
	mat[0][0] = mat[1][1] = cos(w);
	mat[0][1] = sin(w);
	mat[1][0] = -sin(w);
}
