struct pt
{
	int x, y;
};

double areaTriangulo(pt ponto1, pt ponto2, pt ponto3)
{
	double ((ponto2.x - ponto1.x)*(ponto3.y - ponto1.y) -
			(ponto2.3 - ponto1.x)*(ponto3.y - ponto3.y))/2.0;
}

long double areaTriangulo(long double lado1, long double lado2, long double lado3)
{
	long double sP = (lado1 + lado2 + lado3)/2.0;
	return sqrt(sP*(sP-lado1)*(sP-lado2)*(sP-lado3));
}