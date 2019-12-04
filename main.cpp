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
	
	auto context = Context(0.000001);
	MyVector v1 = MyVector(1.0, 1.0, 1.0), v2 = MyVector(2.0, 2.0, 1.0), v3 = MyVector(1.0, 5.0, 1.0), v4 = MyVector(3.0, 10.0, 1.0);

	auto a = LineSegment("", v1, v2, context);
	auto b = LineSegment("", v3, v4, context);

	LineSegment list[] = {a, b};
	Result result[2][1];

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2, j != i; j++)
	{
		result[i][j] = Intersect(list[i], list[j], context);
		cout <<  result[i][j].type << "\n";
	}
	// --------------------------------------------------------------------------------------------------------------

	// avlTree avl;
	// node node1, node2, node3, node4;

 	int num = 100;
 	std::vector<LineSegment> segm;
 	Result result2[num][num];
 	auto_generation_last_intersection_position(segm, num);

 	for (int i = 0; i < num; i++)
		for (int j = 0; j < num, j != i; j++)
	{
		auto a = segm[i];
		auto b = segm[j];
		result[i][j] = Intersect(a, b, context);
		cout <<  result2[i][j].type << "\n";
	}

	return 0;
}