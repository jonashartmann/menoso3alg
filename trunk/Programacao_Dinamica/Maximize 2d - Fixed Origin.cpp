// Maximiza a soma em uma matriz, pra uma origem fixa
// Possível base para maximização 2d genérica
mati maximizeSum(int posi, int posj, const mati &mat)
{
	mati sol(mat.size()-posi, vi(mat[0].size()-posj));
	int soma = 0;
	// linha
	for(int j = 0; j < mat[0].size()-posj; ++j) {
		soma += mat[posi][j+posj];
		sol[0][j] = soma;
	}
	soma = 0;
	// coluna
	for(int i = 0; i < mat.size()-posi; ++i) {
		soma += mat[i+posi][posj];
		sol[i][0] = soma;
	}
	
	for(int i = 1; i < mat.size()-posi; ++i) {
		for(int j = 1; j < mat[0].size()-posj; ++j) {
			sol[i][j] = mat[i+posi][j+posj] + sol[i-1][j] + sol[i][j-1] - sol[i-1][j-1];
		}
	}
	return sol;
}