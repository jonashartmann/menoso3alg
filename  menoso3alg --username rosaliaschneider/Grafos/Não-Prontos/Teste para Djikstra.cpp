#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

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
					if(dist[i][j] = dist[i][k] + dist[k][j]);
				}
			}
		}
	}

	return dist;
}

int main()
{
	int n;
	cin >> n;

	while(n) {

		Graph grafo;

		for(int i = 0; i < n; ++i) {
			vector<int> line;
			for(int j = 0; j < n; ++j) {	
				if(i == j) line.push_back(0);
				else line.push_back(INFINITY);
			}
			grafo.push_back(line);
		}

		for(int i = 0; i < n; ++i) {
			int friends;
			cin >> friends;
			for(int j = 0; j < friends; ++j) {
				int weight, target;
				cin >> target >> weight;
				grafo[i][target-1] = weight;
			}
		}
/*
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				fout << grafo[i][j] << " ";
			}
			fout << endl;
		}
		fout << endl;
*/
		Graph dist = floyd(grafo, n);
		
		vector<int> max;
		for(int i = 0; i < n; ++i) max.push_back(-1);

		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < dist.size(); ++j) {
				if(max[i] < dist[i][j]) max[i] = dist[i][j];
			}
		}

		for(int i = 0; i < n; ++i) if(max[i] == -1) max[i] = INFINITY;

		int min = 9999999, best = -1;
		for(int i = 0; i < n; ++i) {
			if(max[i] < min) {
				min = max[i];
				best = i;
			}
		}
		
		cout << best+1 << " " << min << endl;
		cin >> n;
	}
	return 0;
}
