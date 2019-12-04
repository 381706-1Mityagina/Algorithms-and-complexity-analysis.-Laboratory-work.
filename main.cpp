#include "avl_tree.cpp"
#include "segments_generate.cpp"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
// Naive algorithm
// --------------------------------------------------------------------------------------------------------------
	
	auto context = Context(0.0001);
	
	// MyVector v1 = MyVector(1.0, 1.0, 1.0), v2 = MyVector(2.0, 2.0, 1.0), v3 = MyVector(1.0, 5.0, 1.0), v4 = MyVector(3.0, 10.0, 1.0);
	// auto a = LineSegment("", v1, v2, context);
	// auto b = LineSegment("", v3, v4, context);
	// LineSegment list[] = {a, b, a, b, a, a, b, b};
	// Result result[8][7];
	// for (int i = 0; i < 8; i++)
	// 	for (int j = 0; j < 8, j != i; j++)
	// {
	// 	result[i][j] = Intersect(list[i], list[j], context);
	// 	if (result[i][j].type > 0)
	// 		cout << "Segments " << i << " and " << j << " have intersection type " << result[i][j].type << "\n";
	// }
	// cout << "\n";

// --------------------------------------------------------------------------------------------------------------
	// avlTree avl;
	// node node1, node2, node3, node4;

 	int num = 2003;
 	std::vector<LineSegment> segm;
 	Result result2; //[num][num];
 	auto_generation_last_intersection_position(segm, num);

 	for (int i = 0; i < num; i++)
		for (int j = 0; j < num, j != i; j++)
	{
		auto a = segm[i];
		auto b = segm[j];
		result2 = Intersect(a, b, context);
		if (result2.type > 0)
			cout << "Segments " << i << " and " << j << " have intersection type " << result2.type << "\n";
	}

	return 0;
}