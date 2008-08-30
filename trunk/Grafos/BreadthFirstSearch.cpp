#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
// Grafo é uma matriz de adjacência
typedef vector< vector<int> > Graph;

bool bfs(Graph grafo, int start, int end) {
	queue<int> next;
	vector<int> parent(grafo.size(), -1);
	next.push(start);
	while (!next.empty()) {
		int u = next.front();
		next.pop();
		
		// End condition
		if (u == end) 
			return true;
		
		for (vector<int>::iterator it = grafo[u].begin(); it != grafo[u].end(); ++it){
			// Look through neighbours.
			int v = *it;
			if (parent[v] == -1) {
				// if v is univisited.
				parent[v] = u;
				next.push(v);
			}
		}
	}
	return false;
}

int main() {

}
