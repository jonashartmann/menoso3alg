// Fatoração em números primos
// Retorna um vetor com todos os fatores (inclusive repetidos)
vi primeFac(int number)
{
	vi facs;
	facs.clear();
	
	int n = number;
	while(!(n%2)) {
		facs.push_back(2);
		n /= 2;
	}
	for(int i = 3; i <= sqrt(n)+1;) {
		if(!(n%i)) {
			n /= i;
			facs.push_back(i);
		}
		else i+=2;
	}
	// para numeros primos
	if(n > 1) facs.push_back(n);
	return facs;
}
