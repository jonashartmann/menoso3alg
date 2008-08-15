struct pt
{
	int x, y;
};

double areaPoligono(vector<pt> cHull)
{
	double area = 0.0;
	for(int i = 1; i < cHull.size()-1; ++i) {
		area += ((cHull[i].x - cHull[0].x)*(cHull[i+1].y - cHull[0].y) -
				 (cHull[i].x - cHull[0].x)*(cHull[i+1].y - cHull[0].y))/2.0;
	}
}