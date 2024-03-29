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

//int main_work(int number_of_segments, int gen_or_wr) {
//// Naive algorithm
//// --------------------------------------------------------------------------------------------------------------
//    if (gen_or_wr == 0)
//    {
//        auto context = Context(0.0001);

//    // 	int number_of_segments = 1000;
//        std::vector<LineSegment> segments;
//        Result result2;
//        auto_generation_last_intersection_position_naive(segments, number_of_segments);

//        double t1, t2, dt;
//        t1 = clock();
//        for (int i = 0; i < number_of_segments; i++)
//            for (int j = 0; j < number_of_segments, j != i; j++)
//        {
//            auto a = segments[i];
//            auto b = segments[j];
//            result2 = Intersect(a, b, context);
//            if (result2.type > 0)
//            {
//                break;
//            }
//        }
//        t2 = clock();
//        dt = t2 - t1;
//        std::cout << "TIME naive = " << dt << "\n";
//    // --------------------------------------------------------------------------------------------------------------
//    // Effective algorithm
//    // --------------------------------------------------------------------------------------------------------------
//        std::vector<Point> intersections;
//        std::vector<Segment> segments_new;

//        auto_generation_last_intersection_position_sweep(segments_new, number_of_segments);
//        double t1_2, t2_2, dt_2;
//        t1_2 = clock();
//        intersect(segments_new, intersections, false);
//        // pain_work(segments, number_of_segments);
//        t2_2 = clock();
//        dt_2 = t2_2 - t1_2;
//        std::cout << "TIME effective = " << dt_2 << "\n";
//        if (intersections.size() > 0)
//        {
//            std::vector<Point>::iterator it = intersections.begin();
//            std::cout << " " << "(" << it->x << "," << it->y << ") " << std::endl;
//        }

//        // std::cout << "Intersection points[" << intersections.size() << "]: " << std::endl;
//        // for (std::vector<Point>::iterator it = intersections.begin(); it != intersections.end(); ++it)
//        // 	std::cout << " " << "(" << it->x << "," << it->y << ") " << std::endl;

//        // std::cout << "Segments[" << number_of_segments << "]: " << std::endl;
//        // for (int i = 0; i < number_of_segments; i++)
//        // 	std::cout << "[ " << " " << "(" << segments_new[i].begin.x << "," << segments_new[i].begin.y << "), " << " " << "(" << segments_new[i].end.x << "," << segments_new[i].end.y << ") ] " << std::endl;
//    // --------------------------------------------------------------------------------------------------------------
//    }
//	return 0;
//}
