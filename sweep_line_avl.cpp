//----------------------------------------------//
// ---- EFFECTIVE ALGORITHM with avl trees ---- //
//----------------------------------------------//
#include <vector>
#include <ctime>
#include "avl_tree.cpp"
#include "segments_generate.cpp"
#include <iostream>

// class SweepLineEffective
// {
// public:
// 	LineSegment sweep_line;
	
// 	SweepLineEffective() {
// 		segments = 0;
// 		sweep_line = 0;
// 	}
// 	~SweepLineEffective() {
// 		segments = 0;
// 		sweep_line = 0;
// 	}
// 	// void CheckIntersections(LineSegment *segments, int n);
// };

// sweepLineIntersection(Points[0..2n-1]):
// 1. Sort Points[] from left to right (according to x coordinate)

// 2. Create an empty Self-Balancing BST T. It will contain all active line 
//    Segments ordered by y coordinate.

// // Process all 2n points 
// 3. for i = 0 to 2n-1

//     // If this point is left end of its line  
//     if (Points[i].isLeft) 
//        T.insert(Points[i].line())  // Insert into the tree

//        // Check if this points intersects with its predecessor and successor
//        if ( doIntersect(Points[i].line(), T.pred(Points[i].line()) )
//          return true
//        if ( doIntersect(Points[i].line(), T.succ(Points[i].line()) )
//          return true

//     else  // If it's a right end of its line
//        // Check if its predecessor and successor intersect with each other
//        if ( doIntersect(T.pred(Points[i].line(), T.succ(Points[i].line()))
//          return true
//        T.delete(Points[i].line())  // Delete from tree

// 4. return False

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

void before() {

}

void after() {

}

bool close() {

}

int main()
{
	int number_of_segments = 1000;
	std::vector<LineSegment> segments(number_of_segments);
	avlTree avl;
	Context context = Context(0.000001);

	std::vector<LineSegment> forUsage(number_of_segments);

	for (int i = 0; i < number_of_segments; i++)
	{
		segments[i] = LineSegment("", MyVector(2., 1. - i, 0.), MyVector(-3., 14., 0.), context);
	}
	std::cout << "\n";

	forUsage = CheckIntersections(segments, number_of_segments); 

	for (int i = 0; i < number_of_segments; i++)
		segments[i] = forUsage.at(i);

	// LineSegment try_me;

	// try_me = LineSegment("", MyVector(find_min_x(segments, number_of_segments), find_min_y(segments, number_of_segments), 0.), MyVector(find_min_x(segments, number_of_segments), find_max_y(segments, number_of_segments), 0.), context);

	// for(double i = find_min_x(segments, number_of_segments); i < find_max_x(segments, number_of_segments); i += 0.01)
	// {

	// }

	std::vector<Point> intersections;
	std::vector<Segment> segments_new;

	auto_generation_last_intersection_position_sweep(segments_new, number_of_segments); 
	double t1, t2, dt;
	t1 = clock();
	intersect(segments_new, intersections, false);
	t2 = clock();
	dt = t2 - t1;
	std::cout << "TIME = " << dt << "\n";
	if (intersections.size() > 0)
	{
		std::vector<Point>::iterator it = intersections.begin();
		std::cout << " " << "(" << it->x << "," << it->y << ") " << std::endl;
	}

	// std::cout << "Intersection points[" << intersections.size() << "]: " << std::endl;
	// for (std::vector<Point>::iterator it = intersections.begin(); it != intersections.end(); ++it)
	// 	std::cout << " " << "(" << it->x << "," << it->y << ") " << std::endl;

	// std::cout << "Segments[" << number_of_segments << "]: " << std::endl;
	// for (int i = 0; i < number_of_segments; i++)
	// 	std::cout << "[ " << " " << "(" << segments_new[i].begin.x << "," << segments_new[i].begin.y << "), " << " " << "(" << segments_new[i].end.x << "," << segments_new[i].end.y << ") ] " << std::endl;

	return 0;
}