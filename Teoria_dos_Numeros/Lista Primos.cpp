// Retorna um vetor com primos ateh limit
vi calcPrimes(int limit)
{
	vi primes;
	primes.clear();
	
	for(int i = 2; i <= limit; ++i) {
		bool isP = true;
		for(int j = 0; j < primes.size(); ++j) {
			if(i%primes[j] == 0) {
				isP = false;
				break;
			}
		}
		if(isP) primes.push_back(i);
	}
	return primes;	
}