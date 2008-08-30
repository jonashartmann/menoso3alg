bool sameSide(pt p1, pt p2, pt a, pt b)
{
	v3 ab(a, b);
    v3 cp1 = ab.cross(v3(a, p1));
	v3 cp2 = ab.cross(v3(a, p2));
	if(cp1.z*cp2.z >= 0) return true;
    else return false;
}

bool pointInTriangle(pt p, pt a, pt b, pt c)
{
	if((sameSide(p, a, b, c))&&(sameSide(p, b, a, c))&&(sameSide(p, c, a, b))) return true;
    else return false;
}

bool pointInPolygon(pt point, vector<pt> cHull)
{
	for(int i = 1; i < cHull.size()-1; ++i) {
		if(pointInTriangle(point, cHull[0], cHull[i], cHull[i+1])) return true;
	}
	return false;
}