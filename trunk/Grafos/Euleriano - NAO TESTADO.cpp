#define _CRT_SECURE_NO_DEPRECATE // necessário no VisualC pra tirar uns warnings
#define SIZE 50	// tamanho maximo da matriz do grafo

#include <stdio.h>
#include <stdlib.h>

FILE *out = fopen("out.txt", "w"); // arquivo de saída, usado para teste

// pega o grafo no arquivo
int get_graph(char *filename, int grafo[SIZE][SIZE], int *nro_vert)
{
	FILE *in;
	int lin, col, nro_vertices; 

	in = fopen(filename, "r");	// abre o arquivo

	if(!in) {
		printf("Erro ao abrir arquivo!");
		getchar();
		getchar();
		exit(-1);
	}
	fscanf(in, "%d", &nro_vertices); // le o numero de vertices
	for(lin = 0; lin < nro_vertices; lin++) for(col = 0; col < nro_vertices; col++) grafo[lin][col] = 0;
	while(1) {
		fscanf(in, "%d", &lin);
		if(lin >= nro_vertices) {
			printf("Vertice fora do escopo");
			getchar();
			getchar();
			exit(-1);
		}
		if(lin == -1) break;
		fscanf(in, "%d\n", &col);
		if(col >= nro_vertices) {
			printf("Vertice fora do escopo");
			getchar();
			getchar();
			exit(-1);
		}
		grafo[lin][col] = grafo[col][lin] = 1;
	}
	
	fprintf(out, "   ");
	for(col = 0; col < nro_vertices; col++) fprintf(out, "%02d ", col);
	fprintf(out, "\n");
	for(lin = 0; lin < nro_vertices; lin++) {
		fprintf(out, "%02d ", lin);
		for(col = 0; col < nro_vertices; col++) fprintf(out, "%02d ", grafo[lin][col]);
		fprintf(out, "\n");
	}
	*nro_vert = nro_vertices;
	fclose(in);
	return 0;
}

int get_edges(int grafo[SIZE][SIZE], int nro_vertices) // pega o numero de arestas
{
	int lin, col, arestas = 0;

	for(lin = 0; lin < nro_vertices; lin++) {
		for(col = 0; col < nro_vertices; col++) {
			if(grafo[lin][col]) arestas++;
		}
	}
	return arestas/2;
}

// verifica se tem grau impar ou se eh desconexo
int check_conditions(int grafo[SIZE][SIZE], int nro_vertices)
{
	int lin, a, grau;

//	fprintf(out, "\n\n");

	for(a = 0; a < nro_vertices; a++) {
		grau = 0;
		for(lin = 0; lin < nro_vertices; lin++) if(grafo[a][lin]) grau++;
//		fprintf(out, "%d - %d\n", a , grau);
		if(grau%2) return 1; // Se possuir grau ímpar
		if((!grau)&&(nro_vertices > 1)) return 2; // Grafo desconexo
	}
	return 0; // Se for euleriano
}

// percorre grafo
void walk_thru(int grafo[SIZE][SIZE], int nro_vertices, int lin, int arestas, int nro_arestas, int i, int circuito[SIZE*SIZE])
{
	int col;

 	for(col = 0; col < nro_vertices; col++) {
		if((grafo[lin][col] == 1)&&(col != i)) { // deixa zero por ultimo
			grafo[lin][col] = 2;
			grafo[col][lin] = 2;
			circuito[arestas] = lin;
			circuito[arestas+1] = col;
			arestas++;
			walk_thru(grafo, nro_vertices, col, arestas, nro_arestas, i, circuito);
		}
	}
	if(arestas != nro_arestas) {
		if(grafo[lin][0]==1) walk_thru(grafo, nro_vertices, lin, arestas, nro_arestas, -1, circuito);
		else {
			if(circuito[nro_arestas+1]) {
			grafo[arestas][arestas+1] = 1;
			grafo[arestas+1][arestas] = 1;
			arestas--;
			fprintf(out, "voltei");
			}
		}
	}
	if(arestas == nro_arestas) {
		circuito[nro_arestas+1] = 0;
		return;
	}
}



int main()
{
	int grafo[SIZE][SIZE], grau_impar, nro_vertices, circuito[SIZE*SIZE];
	int c1, arestas;
	char filename[100];

	printf("Digite o nome do arquivo de entrada:");
	scanf("%s", filename);
	get_graph(filename, grafo, &nro_vertices);
	grau_impar = check_conditions(grafo, nro_vertices);
	arestas = get_edges(grafo, nro_vertices);
	if(!grau_impar) {
		printf("Este grafo e Euleriano\n\n");
		circuito[0] = 0;
		walk_thru(grafo, nro_vertices, 0, 0, arestas, 0, circuito);
		for(c1 = 0; c1 < arestas + 1; c1++) printf("%d ", circuito[c1]);
	}
	if(grau_impar == 1) printf("Este grafo possui vertice com grau impar, portanto nao e Euleriano");
	if(grau_impar == 2) printf("Este grafo e desconexo e tem mais de um vertice, portanto nao e Euleriano");
	
	fclose(out);
	getchar();
	getchar();
	return 0;
}
