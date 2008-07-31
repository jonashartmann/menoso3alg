#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* Similaridade de Strings */
// Função que pega o minimo
int min3(int m, int n, int o)
{
	if((m <= n)&&(m <= o)) return m;
	if((n <= m)&&(n <= o)) return n;
	return o;
}
// Funcao que retorna a similaridade
int similarity(string str1, string str2)
{
    int size1 = str1.size();
    int size2 = str2.size();
	vector< vector<int> > matriz(size1+1, size2+1);
	for(int i = 0; i < size1 + 1; i++) {
		matriz[i][0] = i;
	}
	for(int i = 0; i < size2 + 1; i++) {
		matriz[0][i] = i;
	}

	for(int i = 1; i < size1 + 1; i++) {
		for(int j = 1; j < size2 + 1; j++) {
			if(str1[i-1] == str2[j-1])
				matriz[i][j] = matriz[i-1][j-1];
			else
				matriz[i][j] = min3(matriz[i-1][j-1], matriz[i-1][j], matriz[i][j-1]) + 1;
		}
	}
	return matriz[size1][size2];
}
