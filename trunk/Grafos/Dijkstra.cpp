#include <iostream>
#include <stdlib.h>
#include <vector>

#define INF 100000000

using namespace std;
// Grafo é uma matriz de adjacência
typedef vector< vector<int> > Graph;

// Dijkstra
vector<int> dijkstra(Graph grafo, int orig, int dest)
{
	vector<bool> S;	// todos vertices selecionados
	vector<int> pred;	// predecessores
	vector<int> distancias;	// distancia da origem
	vector<bool> V;		// todos vertices menos os selecionados
	
	S.clear();
	S.resize(grafo.size());
	pred.clear();
	pred.resize(grafo.size());
	distancias.clear();
	V.clear();
	V.resize(grafo.size());
	
	for(int i = 0 ; i < grafo.size(); i++){		
		V[i] = true;
		S[i] = false;
		pred[i] = -1;
		if(i != orig) distancias.push_back(INF);
		else distancias.push_back(0);		
	}
	
	while(orig != dest){ 
		S[orig] = true;
		V[orig] = false;		
		// calcula a distancia ateh os vizinhos da origem
		for (int i = 0; i < grafo[orig].size(); i++){		
			if (grafo[orig][i] > 0){
			   if (distancias[i] > (grafo[orig][i] + distancias[orig])){
				  distancias[i] = grafo[orig][i] + distancias[orig];
				  pred[i] = orig;
	  		   }
   			}
		}
		// acha o nodo que tem a menor distancia
		int menor = INF;
		int posmenor = 0;
		for (int i = 0; i < distancias.size(); i++){
			if ((distancias[i] < menor) && (V[i])){
				menor = distancias[i];
				posmenor = i;
			}			
		}
		if (menor == INF){	 	   
  		   break;
  		}
		orig = posmenor;
	}
	return distancias;
}
