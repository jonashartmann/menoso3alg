#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Grafo é uma matriz de adjacência
typedef vector< vector<int> > Graph;

typedef struct caminho_t {
       vector<int> caminhos;
       int tamanho;
};

vector<caminho_t> c;

// Busca em Profundidade
// Retorna os caminhos no vetor de caminhos c definido acima
// Chamada na main, dist = 0
void dfs(Graph grafo, vector<bool> jaFoi, vector<int> sv, int destino, int dist, int maxdist) {
       int origem = sv.back();
       jaFoi[origem] = true;

       if (dist > maxdist)
               return;

       if (origem == destino) {
               caminho_t t;
               t.caminhos = sv;
               t.tamanho = dist;
               c.push_back(t);
               return;
       }

       for (int i = 0; i < grafo.size(); i++) {
               if ((grafo[origem][i] != 0) && (!jaFoi[i])) {
                       int copiaDist = dist + grafo[origem][i];
                       vector<int> copiaOrigem = sv;
                       copiaOrigem.push_back(i);
                       dfs(grafo, jaFoi, copiaOrigem, destino, copiaDist, maxdist);
               }
       }
}

// Comparador usado para ordenar o vetor de caminhos
// Para ordenar use:
// 	sort(c.begin(), c.end(), menor);
bool menor(caminho_t a, caminho_t b) {
       if (a.tamanho < b.tamanho)
               return true;
       if (a.tamanho > b.tamanho)
               return false;
       string sa, sb;
       for (int i = 0; i < a.caminhos.size(); i++)
               sa += a.caminhos[i] + '0';
       for (int i = 0; i < b.caminhos.size(); i++)
               sb += b.caminhos[i] + '0';
       if (sa < sb)
               return true;
       else
               return false;
}

int main() {
}
