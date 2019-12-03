//-------------------------------//
// ---- EFFECTIVE ALGORITHM ---- //
//-------------------------------//

#include <iostream>
#include <vector>
#include <map>
#include <cmath>

struct Point
{
	char letter;
	double x, y;
	Point(const Point & b) : letter(b.letter), x(b.x), y(b.y) {}
	Point(char _letter, double _x, double _y) : letter(_letter), x(_x), y(_y) {}
	Point & operator = (Point const & b) 
	{ 
		letter = b.letter;  
		x = b.x; 
		y = b.y; 
		return *this; 
	}
	bool operator < (const Point & b) const
	{
		if (y < b.y - 1.0e-9) 
			return true;
		else if (y > b.y + 1.0e-9) 
			return false;
		else if (x < b.x - 1.0e-9) 
			return true;
		else 
			return false;
	}
	bool operator == (const Point & b) const
	{
		return fabs(y - b.y) < 1.0e-9 && fabs(x - b.x) < 1.0e-9;
	}
	bool operator != (const Point & b) const
	{
		return fabs(y - b.y) > 1.0e-9 || fabs(x - b.x) > 1.0e-9;
	}
};

struct Segment
{
	Point begin, end;
	Segment(const Segment & b) : begin(b.begin), end(b.end) {}
	Segment(const Point & _beg, const Point & _end) : begin(_beg), end(_end) {}
	Segment & operator = (Segment const & b) 
	{ 
		begin = b.begin; 
		end = b.end; 
		return *this; 
	}
};

#define SEG_START 0
#define SEG_END 1

class event_less
{
public:
	bool operator()(const std::pair<double, int> & a, const std::pair<double, int> & b) const
	{
		if (a.first < b.first - 1.0e-9)
			return true;
		else if (a.first > b.first + 1.0e-9)
			return false;
		else if (a.second < b.second)
			return true;
		return false;
	}
};

std::pair<bool, Point> intersect(const Segment & a, const Segment & b, bool print)
{
	Point ret('a', 0, 0);
	double div = (a.begin.x - a.end.x)*(b.begin.y - b.end.y) - (a.begin.y - a.end.y)*(b.begin.x - b.end.x), t;
	if (fabs(div) < 1.0e-13)
	{
		return std::make_pair(false, ret);
	}
	ret.x = ((a.begin.x * a.end.y - a.begin.y * a.end.x) * (b.begin.x - b.end.x) - (a.begin.x - a.end.x) * (b.begin.x * b.end.y - b.begin.y * b.end.x)) / div;
	ret.y = ((a.begin.x * a.end.y - a.begin.y * a.end.x) * (b.begin.y - b.end.y) - (a.begin.y - a.end.y) * (b.begin.x * b.end.y - b.begin.y * b.end.x)) / div;
	//probably some of these tests are redundant
	if (fabs(a.end.x - a.begin.x) > 1.0e-9) 
	{
		t = (ret.x - a.begin.x) / (a.end.x - a.begin.x);
		if (t < 1.0e-9 || t > 1.0 - 1.0e-9)  
		{
			return std::make_pair(false, ret); 
		}
	}
	if (fabs(a.end.y - a.begin.y) > 1.0e-9)
	{
		t = (ret.y - a.begin.y) / (a.end.y - a.begin.y);
		if (t < 1.0e-9 || t > 1.0 - 1.0e-9)  
		{ 
			return std::make_pair(false, ret); 
		}
	}
	if (fabs(b.end.x - b.begin.x) > 1.0e-9)
	{
		t = (ret.x - b.begin.x) / (b.end.x - b.begin.x);
		if (t < 1.0e-9 || t > 1.0 - 1.0e-9)  
		{ 
			return std::make_pair(false, ret); 
		}
	}
	if (fabs(b.end.y - b.begin.y) > 1.0e-9)
	{
		t = (ret.y - b.begin.y) / (b.end.y - b.begin.y);
		if (t < 1.0e-9 || t > 1.0 - 1.0e-9)  
		{
			return std::make_pair(false, ret); 
		}
	}
	return std::make_pair(true, ret);
}

void intersect(int a, int b, const Point & I, std::vector<Segment> & segments, std::multimap<Point, int> & sweep, std::multimap<std::pair<double,int>, int,event_less> & events, bool print)
{
	//remove event of ending of old segment
	{
		int rem_end_events[2];
		rem_end_events[0] = a;
		rem_end_events[1] = b;
		for (int k = 0; k < 2; ++k)
		{
			std::pair<std::multimap<std::pair<double,int>, int, event_less>::iterator, std::multimap<std::pair<double,int>,int,event_less>::iterator> del = events.equal_range(std::make_pair(segments[rem_end_events[k]].end.x, SEG_END)); //get all events at position of the end
			bool flag = false;
			for (std::multimap<std::pair<double,int>, int,event_less>::iterator it = del.first; it != del.second; ++it) //search over all events
			{
				if (it->first.second == SEG_END && it->second == rem_end_events[k]) //event is end of segment and segment matches current
				{
					events.erase(it); //remove that segment
					flag = true;
					break; //do not expect any more
				}
			}
			if (!flag) 
				std::cout << "Cannot find proper ending event for segment" << std::endl;
		}
	}
	//add new segment with intersection point up to end
	segments.push_back(Segment(I, segments[a].end));
	//add event of starting of new segment
	events.insert(std::make_pair(std::make_pair(I.x, SEG_START), (int)segments.size() - 1));
	//add event of ending of new segment
	events.insert(std::make_pair(std::make_pair(segments.back().end.x, SEG_END),(int)segments.size() - 1));
	//change ending point for current segment
	segments[a].end = I;
	//add event of ending of old segment
	events.insert(std::make_pair(std::make_pair(I.x, SEG_END), a));
	//add new segment with intersection point up to end
	segments.push_back(Segment(I, segments[b].end));
	//add event of starting of new segment
	events.insert(std::make_pair(std::make_pair(I.x,SEG_START), (int)segments.size() - 1));
	//add event of ending of new segment
	events.insert(std::make_pair(std::make_pair(segments.back().end.x, SEG_END), (int)segments.size() - 1));
	//change ending point for current segment
	segments[b].end = I;
	//add event of ending of old segment
	events.insert(std::make_pair(std::make_pair(I.x, SEG_END), b));
}

//find all intersection points
void intersect(std::vector<Segment> & segments, std::vector<Point> & intersections, bool print)
{
	std::multimap<std::pair<double,int>,int,event_less> events;
	std::multimap<Point,int> sweep;

	for (int k = 0; k < (int)segments.size(); ++k)
	{
		if (segments[k].begin.x > segments[k].end.x)
			std::swap(segments[k].begin, segments[k].end);
		events.insert(std::make_pair(std::make_pair(segments[k].begin.x,SEG_START),k));
		events.insert(std::make_pair(std::make_pair(segments[k].end.x,SEG_END), k));
	}
	
	while (!events.empty())
	{
		std::multimap<std::pair<double,int>,int,event_less>::iterator first = events.begin();
		int t = first->first.second;
		int s = first->second;
		events.erase(first);
		if (t == SEG_START)
		{
			//check if there is a line with same position
			std::multimap<Point, int>::iterator ins = sweep.insert(std::make_pair(segments[s].begin, s));
			//check line (or lines above current)
			for (int dir = 0; dir <= 1; ++dir) // look up or down
			{
				std::multimap<Point, int>::iterator iter = ins;
				while ((dir ? ++iter : iter--) != (dir ? sweep.end() : sweep.begin())) //y is greater for next
				{
					if (segments[s].begin != segments[iter->second].begin) //ignore same starting position
					{
						std::pair<bool, Point> I = intersect(segments[s], segments[iter->second],print);
						if (I.first)
						{
							I.second.letter += (char)intersections.size();
							intersections.push_back(I.second);
							intersect(s, iter->second, I.second, segments, sweep, events,print);
						}
					}
					if ((2*dir-1)*(iter->first.y - ins->first.y) > 0) //visited line is above (below) current
						break; //stop search
				}
			}
		}
		else if (t == SEG_END)
		{
			//remove segment from sweep
			std::pair< std::multimap<Point, int>::iterator, std::multimap<Point, int>::iterator > range = sweep.equal_range(segments[s].begin);
			std::multimap<Point, int>::iterator above = range.second, below = range.first;
			bool flag = false, test = true;
			if( below-- == sweep.begin() ) 
				test = false;
			if( above == sweep.end() ) 
				test = false;
			if( test && print ) 
				std::cout << "Test will be performed" << std::endl;
			for (std::multimap<Point, int>::iterator it = range.first; it != range.second; ++it) //search over all events
			{
				if( it->second == s) //found necessery segment
				{
					sweep.erase(it);
					flag = true;
					break; //do not expect any more
				}
			}
			if (!flag) 
				std::cout << __FILE__ << ":" << __LINE__ <<  " Error: cannot find segment " << s << " in sweep" << std::endl;
			if (test)
			{
				if (segments[above->second].begin != segments[below->second].begin)
				{
					std::pair<bool, Point> I = intersect(segments[below->second], segments[above->second],print);
					if (I.first)
					{
						I.second.letter += (char)intersections.size();
						intersections.push_back(I.second);
						intersect(below->second, above->second, I.second, segments, sweep, events,print);
					}
				}
			}
		}
	}
	
}