struct pt
{
	int x, y;
};

double areaPoligono(vector<pt> cHull)
{
	double area = 0.0;
	cHull.push_back(cHull[0]);
	for(int i = 0; i < cHull.size()-1; ++i) {
		area += (cHull[i].x*cHull[i+1].y) - (cHull[i+1].x*cHull[i].y);	
	}
	if(area < 0) area *= -1.0;
	return area/2.0;
}