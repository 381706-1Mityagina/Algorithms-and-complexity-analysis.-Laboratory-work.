//---------------------------//
// ---- NAIVE ALGORITHM ---- //
//---------------------------//
#include "my_vector.h"

double MyVector::GetLength() const 
{
	return pow(X*X + Y*Y + Z*Z, 0.5);
}

MyVector operator-(const MyVector& lhs, const MyVector& rhs) 
{
	return MyVector(lhs.GetX()-rhs.GetX(), lhs.GetY()-rhs.GetY(), lhs.GetZ()-rhs.GetZ());
}

MyVector operator*(double k, const MyVector& v) 
{
	return MyVector(v.GetX()*k, v.GetY()*k, v.GetZ()*k);
}

ostream& operator<<(ostream& os, const MyVector& v) 
{
	os << '(' << v.GetX() << ',' << v.GetY() << ',' << v.GetZ() << ')';
	return os;
}

//Считает векторное произведение
MyVector CrossProduct(const MyVector& lhs, const MyVector& rhs) 
{
	return MyVector(lhs.GetY()*rhs.GetZ() - lhs.GetZ()*rhs.GetY(),
					-lhs.GetX()*rhs.GetZ() + lhs.GetZ()*rhs.GetX(),
					lhs.GetX()*rhs.GetY() - lhs.GetY()*rhs.GetX()
					);
}

//Считает скалярное произведение
double ScalarProduct(const MyVector& lhs, const MyVector& rhs) 
{
	return lhs.GetX()*rhs.GetX() + lhs.GetY()*rhs.GetY() + lhs.GetZ()*rhs.GetZ();
}
