typedef vector< vector<int> > Graph;
#define INFINITY 9999999

// Graph - matriz de adjacência
// inicializacao: aresta A->A = peso 0
//				  aresta inexistente = peso INFINITY
Graph floyd(Graph graph, int size)
{
	Graph dist;

	for(int i = 0; i < size; ++i) {
		vector<int> d;
		for(int j = 0; j < size; ++j) d.push_back(graph[i][j]);
		dist.push_back(d);
	}

	for(int k = 0; k < size; ++k) {
		for(int i = 0; i < size; ++i) {
			for(int j = 0; j < size; ++j) {
				if(dist[i][j] > dist[i][k] + dist[k][j]) {
					if(dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	return dist;
}



