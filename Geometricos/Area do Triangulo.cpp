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

// Não testado
double areaTriangulo(pt ponto1, pt ponto2, pt ponto3)
{
	v3 vec1(p1, p2), vec2(p1, p3);
	return vec1.cross(vec2).norm()/2.0;
}
	

