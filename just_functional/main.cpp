#include "avl_tree.cpp"
#include "segments_generate.cpp"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

int main() {
// Naive algorithm
// --------------------------------------------------------------------------------------------------------------
	
	auto context = Context(0.0001);

 	int num = 1000;
 	std::vector<LineSegment> segm;
 	Result result2;
 	auto_generation_last_intersection_position_naive(segm, num);

 	double t1, t2, dt;
 	t1 = clock();
 	for (int i = 0; i < num; i++)
		for (int j = 0; j < num, j != i; j++)
	{
		auto a = segm[i];
		auto b = segm[j];
		result2 = Intersect(a, b, context);
		if (result2.type > 0) {
			// cout << "Segments " << i << " and " << j << " have intersection type " << result2.type << "\n";
			break;
		}
	}
	t2 = clock();
	dt = t2 - t1;
	std::cout << "TIME = " << dt << "\n";
// --------------------------------------------------------------------------------------------------------------
// Effective algorithm
// --------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------

	return 0;
}