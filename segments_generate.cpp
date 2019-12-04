#include "intersect.cpp"

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

void auto_generation_last_intersection_position(std::vector<LineSegment> &segments, int number_of_segments) {
	for (int i = 0; i < number_of_segments - 2; i++) {
		// segments[i].start.X = i;
		// segments[i].end.X = i + 0,5;
		// segments[i].start.Y = 1;
		// segments[i].end.Y = 4;
		// segments[i].start.Z = segments[i].end.Z = 0;

		segments.push_back(LineSegment("", MyVector(float(i), 1.0, 0.0), MyVector(float(i) + 0.5, 4.0, 0.0), Context(0.000001)));
	}

	segments.push_back(LineSegment("", MyVector(float(number_of_segments), 1.0, 0.0), MyVector(float(number_of_segments) + 3.0, 4.0, 0.0), Context(0.000001)));
	segments.push_back(LineSegment("", MyVector(float(number_of_segments) + 2.0, 1.0, 0.0), MyVector(float(number_of_segments) + 1.0, 4.0, 0.0), Context(0.000001)));

	// segments[number_of_segments - 2].start.X = number_of_segments - 2 + 2;
	// segments[number_of_segments - 2].end.X = number_of_segments - 2 + 4;
	// segments[number_of_segments - 2].start.Y = 1;
	// segments[number_of_segments - 2].end.Y = 4;
	// segments[number_of_segments - 1].start.X = number_of_segments - 1 + 2;
	// segments[number_of_segments - 1].end.X = segments[number_of_segments - 2].start.Y + 1;
	// segments[number_of_segments - 1].start.Y = 1;
	// segments[number_of_segments - 1].end.Y = 4;
	// segments[number_of_segments - 2].start.Z = segments[number_of_segments - 2].end.Z = segments[number_of_segments - 1].start.Z = segments[number_of_segments - 1].end.Z = 0;

	// return segments;
}

void using_input() {

}