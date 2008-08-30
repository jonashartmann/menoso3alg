#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct pt
{
	int x, y;
};

bool menor(pt p1, pt p2)
{
	if(p1.x < p2.x) return true;
	if(p1.x > p2.x) return false;
	if(p1.y < p2.y) return true;
	return false;
}

bool turnLeft(pt p0, pt p1, pt p2)
{
	int a = (p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);
	if(a <= 0) return true;
	return false;
}

vector<pt> convexHull(vector<pt> points) 
{
	vector<pt> upper, lower;
	upper.clear();
	lower.clear();

	sort(points.begin(), points.end(), menor);

	upper.push_back(points[0]);
	upper.push_back(points[1]);
	for(int i = 2; i < points.size(); ++i) {
		upper.push_back(points[i]);
		while((upper.size() > 2)&&(turnLeft(upper[upper.size()-1], upper[upper.size()-2], upper[upper.size()-3]))) {
			upper.erase(upper.end()-2);
		}
	}
	lower.push_back(points[points.size()-1]);
	lower.push_back(points[points.size()-2]);
	for(int i = points.size()-3; i >= 0; --i) {
		lower.push_back(points[i]);
		while((lower.size() > 2)&&(turnLeft(lower[lower.size()-1], lower[lower.size()-2], lower[lower.size()-3]))) {
			lower.erase(lower.end()-2);
		}
	}
	lower.erase(lower.begin());
	lower.erase(lower.end()-1);
	upper.insert(upper.end(), lower.begin(), lower.end());
	return upper;
}