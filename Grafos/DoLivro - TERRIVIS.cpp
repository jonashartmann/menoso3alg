#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

// Aresta
typedef struct {
	// vertice adjacente
	int v;
	// peso
	int weight;
} edge;

// Lista de adjacência
typedef struct {
	// representa cada vertice com suas arestas adjacentes (v. adjacentes e peso)
	vector< vector<edge> > edges;
	// numero de vertices/arestas do grafo
	int nvertices;
	int nedges;
} graph;

// Inicializa
void initialize_graph(graph *g, int nvertices)
{
	g->nvertices = 0;
	g->nedges = 0;

	g->edges.clear();
	g->edges.reserve(nvertices);

	for(int i = 0; i < nvertices; i++)
		g->edges[i].clear();
}

// Insere aresta
void insert_edge(graph *g, int x, int y, bool directed, int weight)
{
	edge qualquer;
	qualquer.v = y;
	qualquer.weight = weight;
	g->edges[x].push_back(qualquer);

	if(directed == false)
		insert_edge(g, y, x, true, weight);
	else
		++(g->nedges);
}

// Lê grafo
void read_graph(graph *g, bool directed)
{
	int nvertices, nedges;
	int x, y, weight;

	cin >> nvertices >> nedges;

	initialize_graph(g, nvertices);

	for(int i = 0; i < g->nvertices; i++) {
		cin >> x >> y >> weight;
		insert_edge(g, x, y, directed, weight);
	}
}

vector<bool> processed;   // which vertices have been processed
vector<bool> discovered;  // which vertices have been found
vector<int> parent;       // discovery relation

// Inicializa para busca
void initialize_search(graph *g)
{
	processed.clear();
	processed.resize(g->nvertices);
	discovered.clear();
	discovered.resize(g->nvertices);
	parent.clear();
	parent.resize(g->nvertices);

	for(int i = 0; i < g->nvertices; i++) {
		processed[i] = discovered[i] = false;
		parent[i] = -1;
	}
}

// Busca em amplitude
void bfs(graph *g, int start)
{
	vector<int> q; // fila de vertices a visitar
	int v;         // vertice atual

	q.clear();
	q.push_back(start);
	discovered[start] = true;

	while(q.empty() == false) {
		v = q.front();
		q.erase(q.begin());
		//process_vertex(v);
		processed[v] = true;
		for(int i = 0; i < g->edges[v].size(); i++) {

			if(discovered[g->edges[v][i].v] == false) {
				q.push_back(g->edges[v][i].v);
				discovered[g->edges[v][i].v] = true;
				parent[g->edges[v][i].v] = v;
			}
			//if(processed[g->edges[v][i]] == FALSE)
			//	process_edge(v,g->edges[v][i]);
		}
	}
}

// Encontra caminho entre start e end a partir dos pais
// (funciona isso? e se o final tiver mais de um pai?)
void find_path(int start, int end, int parents[])
{
	if((start == end)||(end == -1))
		cout << endl << start;
	else {
		find_path(start, parents[end], parents);
		cout << " " << end;
	}
}

// Busca em profundidade
void dfs(graph *g, int v)
{
	int y;  // vertice sucessor

//	if(finished) return;

	discovered[v] = true;
//	process_vertex(v);

	for(int i = 0; i < g->edges[v].size(); i++) {
		y = g->edges[v][i].v;
		if(discovered[y] == false) {
			parent[y] = v;
			dfs(g, y);
//			else if (processed[y] == false)
//				process_edge(v, y);
		}
//		if (finished) return;
	}

//	processed[v] = true;
}

// Componentes conexos
void connected_components(graph *g)
{
	int c;

	initialize_search(g);

	c = 0;
	for(int i = 0; i < g->nvertices; i++)
		if(discovered[i] == false) {
			c++;
//                        printf("Component %d:",c);
			dfs(g, i);
//                        printf("\n");
		}
}

// Calcula o numero de vertices que entram em cada vertice
void compute_indegrees(graph *g, int in[])
{
	for (int i = 0; i < g->nvertices; i++)
		in[i] = 0;

	for (int i = 0; i < g->nvertices; i++)
		for (int j = 0; j < g->edges[i].size(); j++)
			in[ g->edges[i][j].v ] ++;
}

// Não olhei
void topsort(graph *g, int sorted[])
{
	int indegree[g->nvertices];             /* indegree of each vertex */
	vector<int> zeroin;                   /* vertices of indegree 0 */
	int x, y;                       /* current and next vertex */
	int j;                       /* counters */

	compute_indegrees(g, indegree);
	zeroin.clear();
	for (int i = 0; i < g->nvertices; i++)
		if (indegree[i] == 0)
			zeroin.push_back(i);

	j = 0;
	while (!zeroin.empty()) {
		j = j + 1;
		x = zeroin.front();
		zeroin.erase(zeroin.begin());
		sorted[j] = x;
		for (int i = 0; i < g -> edges[x].size(); i++) {
			y = g -> edges[x][i].v;
			indegree[y]--;
			if (indegree[y] == 0)
				zeroin.push_back(y);
		}
	}

	if (j != g->nvertices)
		printf("Not a DAG -- only %d vertices found\n", j);
}

void prim(graph *g, int start)
{
	bool intree[g -> nvertices];              /* is vertex in the tree yet? */
	int distance[g -> nvertices];             /* vertex distance from start */
	int v;                          /* current vertex to process */
	int w;                          /* candidate next vertex */
	int weight;                     /* edge weight */
	int dist;                       /* shortest current distance */
	unsigned long long MAXINT = 2147483647;

	for (int i = 0; i < g -> nvertices; i++) {
		intree[i] = false;
		distance[i] = MAXINT;
		parent[i] = -1;
	}

	distance[start] = 0;
	v = start;

	while (intree[v] == false) {
		intree[v] = true;
		for (int i = 0; i < g->edges[v].size(); i++) {
			w = g->edges[v][i].v;
			weight = g->edges[v][i].weight;
			if ((distance[w] > weight) && (intree[w] == false)) {
				distance[w] = weight;
				parent[w] = v;
			}
		}

		v = 0;
		dist = MAXINT;
		for (int i = 1; i < g->nvertices; i++)
			if ((intree[i] == false) && (dist > distance[i])) {
				dist = distance[i];
				v = i;
			}
	}
}

void dijkstra(graph *g, int start) {
	bool intree[g -> nvertices];              /* is vertex in the tree yet? */
	int distance[g -> nvertices];             /* vertex distance from start */
	int v;                          /* current vertex to process */
	int w;                          /* candidate next vertex */
	int weight;                     /* edge weight */
	int dist;                       /* shortest current distance */
	unsigned long long MAXINT = 2147483647;

	for (int i = 0; i < g -> nvertices; i++) {
		intree[i] = false;
		distance[i] = MAXINT;
		parent[i] = -1;
	}

	distance[start] = 0;
	v = start;

	while (intree[v] == false) {
		intree[v] = true;
		for (int i = 0; i < g->edges[v].size(); i++) {
			w = g->edges[v][i].v;
			weight = g->edges[v][i].weight;
			if (distance[w] > (distance[v] + weight)) {
				distance[w] = distance[v] + weight;
				parent[w] = v;
			}
		}

		v = 0;
		dist = MAXINT;
		for (int i = 1; i < g->nvertices; i++)
			if ((intree[i] == false) && (dist > distance[i])) {
				dist = distance[i];
				v = i;
			}
	}
}

typedef struct {
	vector< vector<int> > weight; //adjacency/weight info
	int nvertices;                 /* number of vertices in graph */
} adjacency_matrix;

void initialize_adjacency_matrix(adjacency_matrix *g, int nvertices) {
	g -> weight.clear();
	g -> weight.resize(nvertices);
	for (int i = 0; i < nvertices; i++) {
		g -> weight[i].clear();
		g -> weight[i].resize(nvertices);
	}

	g -> nvertices = nvertices;

	for (int i = 0; i < nvertices; i++)
		for (int j = 0; j < nvertices; j++)
			g->weight[i][j] = 2147483647;
}

void floyd(adjacency_matrix *g) {
	int through_k;        /* distance through vertex k */

	for (int k = 0; k < g->nvertices; k++)
		for (int i = 0; i < g->nvertices; i++)
			for (int j = 0; j < g->nvertices; j++) {
				through_k = g->weight[i][k] + g->weight[k][j];
				if (through_k < g->weight[i][j])
					g->weight[i][j] = through_k;
			}
}

int main() {
	return 0;
}
