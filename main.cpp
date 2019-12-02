#include "intersect.cpp"
#include "avl_tree.cpp"
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
	MyVector v1 = MyVector(1.0,1.0,1.0), v2 = MyVector(2.0,2.0,1.0), v3 = MyVector(1.0,5.0,1.0), v4 = MyVector(3.0,10.0, 1.0);

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
	//root = avl.insert(root, );
	// --------------------------------------------------------------------------------------------------------------

	avlTree avl;
	node node1, node2, node3, node4;
	
	// vector<Line*> lines;

	// avl.newNode(v1.GetY());
	// avl.newNode(v2.GetY());
	// avl.newNode(v3.GetY());
	// avl.newNode(v4.GetY());

	return 0;
}