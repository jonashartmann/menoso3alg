long double inCircleRadius(long double lado1, long double lado2, long double lado3)
{
	long double p = (lado1 + lado2 + lado3);
	long double a = areaTriangulo(lado1, lado2, lado3)
	return (2*a)/p;
}