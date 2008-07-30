struct pt
{
	int x, y;
};

struct v3
{
	v3() {}
	v3(pt orig, pt dest) {
		x = dest.x - orig.x;
		y = dest.y - orig.y;
		z = 0;
	}

	v3 cross(const v3 &other)
	{
		v3 v;

		v.x = y*other.z - other.y*z;
		v.y = z*other.x - other.z*x;
		v.z = x*other.y - other.x*y;

		return v;
	}

	double norm() {
		return sqrt(x*x + y*y + z*z);
	}

	int x, y, z;

};

vector<pt> convexHull(vector<pt> points) 
{
	vector<pt> cHull;
	cHull.clear();

	int p = 0;
	for(int i = 1; i < points.size(); ++i) {
		if((points[i].y < points[p].y)||
		  ((points[i].y == points[p].y)&&(points[i].x < points[p].x))) {
			p = i;
		}
	}

	int start = p;
	do {
		cHull.push_back(points[p]);
		int n = -1;
		for(int i = 0; i < points.size(); ++i) {
			if(i == p) continue;
			if(n == -1) n = i;
			v3 vecI(points[p], points[i]);
			v3 vecN(points[p], points[n]);
			v3 cross = vecI.cross(vecN);
			if((cross.z > 0)||
			  ((cross.z == 0)&&(vecI.norm() > vecN.norm()))) {
				n = i;
			}
		}
		p = n;
	}
	while(start != p);

	return cHull;
}