//----------------------------------------------//
// ---- EFFECTIVE ALGORITHM with avl trees ---- //
//----------------------------------------------//
#include <vector>
#include "avl_tree.cpp"
#include "line_segment.cpp"
#include <iostream>

class SweepLineEffective
{
public:
	LineSegment *segments;
	LineSegment sweep_line;
	
	SweepLineEffective();
	// void CheckIntersections(LineSegment *segments, int n);
};

std::vector<LineSegment> CheckIntersections(LineSegment *segments, int number_of_segments) {
	std::vector<LineSegment> forSorting(number_of_segments), forUsage(number_of_segments);

	for (int i = 0; i < number_of_segments; i++)
		forSorting.at(i) = segments[i];

	forUsage = sort_y(forSorting, number_of_segments);
	
	return forUsage;
}

double find_min_x(std::vector<LineSegment> segments, int number_of_segments) {
	double min_x = segments[i].start.GetX();
	for (int i = 0; i < number_of_segments; i++)
	{
		if (segments[i].start.GetX() < min_x)
			min_x = segments[i].start.GetX();
		if (segments[i].end.GetX() < min_x)
			min_x = segments[i].end.GetX();
	}
	return min_x;
}

double find_min_y(std::vector<LineSegment> segments, int number_of_segments) {
	double min_x = segments[i].start.GetY();
	for (int i = 0; i < number_of_segments; i++)
	{
		if (segments[i].start.GetY() < min_x)
			min_x = segments[i].start.GetY();
		if (segments[i].end.GetY() < min_x)
			min_x = segments[i].end.GetY();
	}
	return min_x;
}

int main()
{
	int number_of_segments = 5;
	LineSegment segments[number_of_segments];
	avlTree avl;

	std::vector<LineSegment> forUsage(number_of_segments);

	for (int i = 0; i < number_of_segments; i++)
	{
		segments[i] = LineSegment(" A", MyVector(2., 1. - i, 0.), MyVector(-3., 14., 0.), Context(0.000001));
		std::cout << "segment " << i << " start Y is " << segments[i].start.GetY() << std::endl;
	}
	std::cout << "\n";

	forUsage = CheckIntersections(segments, number_of_segments); 

	for (int i = 0; i < number_of_segments; i++)
		segments[i] = forUsage.at(i);

	for (int i = 0; i < number_of_segments; i++)
	{
		std::cout << "segment " << i << " start Y is " << segments[i].start.GetY() << std::endl;
	}

	for (int i = 0; i < number_of_segments; i++)
	{
		avl.newNode(forUsage[i].start.GetY());
	}

	SweepLineEffective sweep_line;
	// LineSegment for_sweep_line = LineSegment("", MyVector(find_min_x(segments, number_of_segments) - 1, find_min_y(segments, number_of_segments) - 1, 0), MyVector(find_min_x(segments, number_of_segments) - 1, find_max_y(segments, number_of_segments) + 1, 0), Context(0.000001))

	return 0;
}