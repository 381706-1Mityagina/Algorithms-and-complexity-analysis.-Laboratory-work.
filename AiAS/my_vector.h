//---------------------------//
// ---- NAIVE ALGORITHM ---- //
//---------------------------//
#include <iostream>
#include <cmath>

using namespace std;

class MyVector 
{
public:
	double X;
	double Y;
	double Z;

	int segment_number;
	int start_or_end;  // 0 = start, 1 = end
public:
	MyVector() : X(0.0), Y(0.0), Z(0.0), segment_number(0), start_or_end(-1) {}
	MyVector(double x, double y, double z) {
		X = x;
		Y = y;
		Z = z;
	}
	~MyVector();

	MyVector(double x, double y, double z, int segment_number, int start_or_end) : X(x), Y(y), Z(z) {}

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
ostream& operator<<(ostream& os, const MyVector& v)
{
    if (v.start_or_end > 0)
        os << '(' << v.GetX() << ',' << v.GetY() << ',' << v.GetZ() << ')' << " which is " << "the end" << " of segment " << v.segment_number << "\n";
    else
        os << '(' << v.GetX() << ',' << v.GetY() << ',' << v.GetZ() << ')' << " which is " << "the start" << " of segment " << v.segment_number << "\n";

    return os;
}

MyVector operator- (const MyVector& lhs, const MyVector& rhs);

MyVector operator* (double k, const MyVector& v);

ostream& operator<< (ostream& os, const MyVector& v);

//Считает векторное произведение
MyVector CrossProduct(const MyVector& lhs, const MyVector& rhs);

//Считает скалярное произведение
double ScalarProduct(const MyVector& lhs, const MyVector& rhs);
