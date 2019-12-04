//---------------------------//
// ---- NAIVE ALGORITHM ---- //
//---------------------------//
#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class MyVector 
{
public:
	double X;
	double Y;
	double Z;
public:
	MyVector() : X(0.0), Y(0.0), Z(0.0) {}
	~MyVector();
	MyVector(double x, double y, double z) : X(x), Y(y), Z(z) {}

	double GetX() const 
	{
		return X;
	}
	double GetY() const 
	{
		return Y;
	}
	double GetZ() const 
	{
		return Z;
	}
	//Длина вектора
	double GetLength() const;
};

MyVector operator- (const MyVector& lhs, const MyVector& rhs);

MyVector::~MyVector()
{
	X = Y = Z = 0;
}

MyVector operator* (double k, const MyVector& v);

ostream& operator<< (ostream& os, const MyVector& v);

//Считает векторное произведение
MyVector CrossProduct(const MyVector& lhs, const MyVector& rhs);

//Считает скалярное произведение
double ScalarProduct(const MyVector& lhs, const MyVector& rhs);