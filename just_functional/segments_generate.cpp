#include "intersect.cpp"
#include "sweep_line.cpp"

// Need to implement the following:

// 1. Generate segments and make some of them intersect
// 2. Make choosing it's indexes possible 
// 3. QT vizualization 
// 4. Report
// 5. Main
// 6. Experiments

void auto_generation_choose_length() {

}

void auto_generation_choose_angle() {

}

void auto_generation_last_intersection_position_naive(std::vector<LineSegment> &segments, int number_of_segments) {
	for (int i = 0; i < number_of_segments - 2; i++) {
		segments.push_back(LineSegment("", MyVector(float(i) / 10, 1.0, 0.0, i, 0), MyVector(float(i) / 10 + 0.5, 4.0, 0.0, i, 1), Context(0.0001)));
	}

	segments.push_back(LineSegment("", MyVector(float(number_of_segments) / 10, 1.0, 0.0, number_of_segments - 2, 0), MyVector(float(number_of_segments) / 10 + 3.0, 4.0, 0.0, number_of_segments - 2, 1), Context(0.0001)));
	segments.push_back(LineSegment("", MyVector(float(number_of_segments) / 10 + 2.0, 1.0, 0.0, number_of_segments - 1, 0), MyVector(float(number_of_segments) / 10 + 1.0, 4.0, 0.0, number_of_segments - 1, 1), Context(0.0001)));
}

void auto_generation_last_intersection_position_sweep(std::vector<Segment> &segments, int number_of_segments) {
	for (int i = 0; i < number_of_segments - 2; i++) {
		segments.push_back(Segment(Point(' ', float(i) / 10, 1.0), Point(' ', float(i) / 10 + 0.5, 4.0)));
	}

	segments.push_back(Segment(Point(' ', float(number_of_segments) / 10, 1.0), Point(' ', float(number_of_segments) / 10 + 3.0, 4.0)));
	segments.push_back(Segment(Point(' ', float(number_of_segments) / 10 + 2.0, 1.0), Point(' ', float(number_of_segments) / 10 + 1.0, 4.0)));
}

void using_input(std::vector<LineSegment> &segments, int number_of_segments) {
	double begin_x, begin_y, end_x, end_y;
	for (int i = 0; i < number_of_segments; i++) {
		std::cout << "Segment start x :\n";
		std::cin >> begin_x;
		std::cout << "Segment start y :\n";
		std::cin >> begin_y;
		std::cout << "Segment end x :\n";
		std::cin >> end_x;
		std::cout << "Segment end y :\n";
		std::cin >> end_y;

		segments.push_back(LineSegment("", MyVector(begin_x, begin_y, 0.0), MyVector(end_x, end_y, 0.0), Context(0.0001)));
	}
}