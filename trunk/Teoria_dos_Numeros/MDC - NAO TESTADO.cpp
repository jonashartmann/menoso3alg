// Maximo divisor comum
int MDC(int a, int b)
{
	if(b > a) {
		int aux = b;
		b = a;
		a = aux;
	}
	if(b == 0) return a;
	return MDC(b, a%b);
}



