//----------------------------------------------//
// ---- EFFECTIVE ALGORITHM with avl trees ---- //
//----------------------------------------------//
#include <vector>
#include "avl_tree.cpp"
#include "sweep_line.cpp"
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

std::vector<LineSegment> CheckIntersections(std::vector<LineSegment> segments, int number_of_segments) {
	std::vector<LineSegment> forSorting(number_of_segments), forUsage(number_of_segments);

	for (int i = 0; i < number_of_segments; i++)
		forSorting.at(i) = segments[i];

	forUsage = sort_y(forSorting, number_of_segments);
	
	return forUsage;
}

double find_min_x(std::vector<LineSegment> segments, int number_of_segments) {
	double min_x = segments[0].start.GetX();
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
	double min_y = segments[0].start.GetY();
	for (int i = 0; i < number_of_segments; i++)
	{
		if (segments[i].start.GetY() < min_y)
			min_y = segments[i].start.GetY();
		if (segments[i].end.GetY() < min_y)
			min_y = segments[i].end.GetY();
	}
	return min_y;
}

double find_max_y(std::vector<LineSegment> segments, int number_of_segments) {
	double max_y = segments[0].start.GetY();
	for (int i = 0; i < number_of_segments; i++)
	{
		if (segments[i].start.GetY() > max_y)
			max_y = segments[i].start.GetY();
		if (segments[i].end.GetY() > max_y)
			max_y = segments[i].end.GetY();
	}
	return max_y;
}

int main()
{
	int number_of_segments = 10;
	std::vector<LineSegment> segments(number_of_segments);
	avlTree avl;

	std::vector<LineSegment> forUsage(number_of_segments);

	for (int i = 0; i < number_of_segments; i++)
	{
		segments[i] = LineSegment("", MyVector(2., 1. - i, 0.), MyVector(-3., 14., 0.), Context(0.000001));
	}
	std::cout << "\n";

	forUsage = CheckIntersections(segments, number_of_segments); 

	for (int i = 0; i < number_of_segments; i++)
		segments[i] = forUsage.at(i);

	std::vector<Point> intersections;
	std::vector<Segment> segments_new;

	for (int i = 0; i < number_of_segments; i++)
	{
		segments_new.push_back(Segment(Point(' ', -i + 3, i + 1), Point(' ', 2 * i - 1, -i + 1)));
	}

	intersect(segments_new, intersections, false);

	std::cout << "Intersection points[" << intersections.size() << "]: " << std::endl;
	for (std::vector<Point>::iterator it = intersections.begin(); it != intersections.end(); ++it)
		std::cout << " " << "(" << it->x << "," << it->y << ") " << std::endl;

	std::cout << "Segments[" << number_of_segments << "]: " << std::endl;
	for (int i = 0; i < number_of_segments; i++)
		std::cout << "[ " << " " << "(" << segments_new[i].begin.x << "," << segments_new[i].begin.y << "), " << " " << "(" << segments_new[i].end.x << "," << segments_new[i].end.y << ") ] " << std::endl;

	return 0;
}