// Verifica se um grafo é euleriano
// n - numero de vertices
// (apenas p/ nao-direcionados)
bool ehEuleriano(mati graph, int n)
{
	for(int i = 0; i < n; ++i) {
		int grau = 0;
		for(int j = 0; j < n; ++j) if(grafo[i][j]) grau++;
		if(grau%2) return false; // se tem grau ímpar
		if((!grau)&&(nro_vertices > 1)) return false; // desconexo
	}
	return true;
}