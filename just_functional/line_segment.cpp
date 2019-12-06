#include "my_vector.cpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

//---------------------------//
// ---- NAIVE ALGORITHM ---- //
//---------------------------//
using namespace std;

struct Context 
{
	double precision; // точность
	Context(double precision_) : precision(precision_) {}
	bool EqualToZero(double x) const 
	{
		return fabs(x) <= precision;
	}
};

class LineSegment 
{
public:
	MyVector start;
	MyVector end;
	string name;

	LineSegment();
	LineSegment(string n, MyVector s, MyVector e, Context context);
	LineSegment(MyVector s, MyVector e);

	MyVector GetStart() const 
	{
		return start;
	}
	
	MyVector GetEnd() const 
	{
		return end;
	}

	string GetName() const 
	{
		return name;
	}
};

ostream& operator<<(ostream& os, const LineSegment& seg);

// -------------------------------------------------------------------------------------------------
LineSegment::LineSegment() 
{
	start = MyVector();
	end = MyVector();
}
// -------------------------------------------------------------------------------------------------
LineSegment::LineSegment(string n, MyVector s, MyVector e, Context context) 
{
	if ((s-e).GetLength() <= context.precision) 
	{
		throw invalid_argument("");
	}
	else 
	{
		name = n;
		start = s;
		end = e;
	}
}
// -------------------------------------------------------------------------------------------------
LineSegment::LineSegment(MyVector s, MyVector e) 
{
	string _name = "";
	name = _name;
	Context context = Context(0.000001);
	if ((s-e).GetLength() <= context.precision) 
	{
		throw invalid_argument("");
	}
	else 
	{
		start = s;
		end = e;
	}
}
// -------------------------------------------------------------------------------------------------
ostream& operator<<(ostream& os, const LineSegment& seg) 
{
	os << "Start: " << seg.GetStart() << "; End: " << seg.GetEnd();
	return os;
}
// -------------------------------------------------------------------------------------------------
LineSegment getSegmentByY(double _y, std::vector<LineSegment> input, int number_of_segments)
{
	int i;
	for (i = 0; i < number_of_segments; i++)
	{
		if (input[i].start.GetY() == _y)
			break;
	}
	return input[i];
}

MyVector getPointByX(double _x, std::vector<LineSegment> input, int number_of_segments) 
{
	int i;
	for (i = 0; i < 2 * number_of_segments; i++)
	{
		if (input[i].start.GetX() == _x)
		{
			return input[i].start;
			break;
		}
		if (input[i].end.GetX() == _x)
		{
			return input[i].end;
			break;
		}
	}
}
// -------------------------------------------------------------------------------------------------
std::vector<LineSegment> sort_y(std::vector<LineSegment> input, int number_of_segments)
{
	std::vector<LineSegment> output(number_of_segments);
	std::vector<double> y_component(number_of_segments);

	for (int i = 0; i < number_of_segments; i++)
		y_component[i] = input.at(i).start.GetY(); 
	
	sort(y_component.begin(), y_component.end());

	for (int i = 0; i < number_of_segments; i++)
	{
		output.at(i) = getSegmentByY(y_component.at(i), input, number_of_segments);
	}

	return output;
}

std::vector<MyVector> sort_x_points(std::vector<LineSegment> input, int number_of_segments)
{
	std::vector<MyVector> output(2 * number_of_segments);
	std::vector<double> x_component(2 * number_of_segments);

	for (int i = 0; i < number_of_segments; i++)
		x_component[i] = input[i].start.GetX(); 
	for (int i = number_of_segments; i < 2 * number_of_segments; i++)
		x_component[i] = input[i].end.GetX(); 
	
	sort(x_component.begin(), x_component.end());

	for (int i = 0; i < 2 * number_of_segments; i++)
	{
		output.at(i) = getPointByX(x_component[i], input, number_of_segments);
	}

	return output;
}
// -------------------------------------------------------------------------------------------------
