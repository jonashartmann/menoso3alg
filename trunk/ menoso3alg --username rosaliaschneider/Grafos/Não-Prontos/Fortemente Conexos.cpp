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
		grafo[lin][col] = 1; //  alterado para pegar grafo orientado
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

// verifica se valor pertence ao arranjo
int pertence(int valor, int arranjo[SIZE])
{
	int c1; 
	for(c1 = 0; c1 < SIZE; c1++) if(arranjo[c1] == valor) return 1;
	return 0;
}

// parte recursiva da funcao que calcula o tau
void tau_rec(int grafo[SIZE][SIZE], int nro_vertices, int lin, int faz_parte[SIZE], int *aux)
{
	int col, i;
	
	if(faz_parte[0] == -1) {
		faz_parte[0] = lin;
		i = *aux;
		i++;
		*aux = i;
	}

	for(col = 0; col < nro_vertices; col++) {
		if((grafo[lin][col] == 1)&&(!pertence(col, faz_parte))) {
			i = *aux;
			faz_parte[i] = col;
			i++;
			*aux = i;	
			tau_rec(grafo, nro_vertices, col, faz_parte, aux);
		}
	}
	return;
}


// parte nao-recursiva (inicializacao) da funcao que calcula o tau
void tau(int grafo[SIZE][SIZE], int nro_vertices, int lin, int faz_parte[SIZE])
{
	int *aux, c1;

	aux = (int *)malloc(sizeof(int));
	*aux = 0;
	for(c1 = 0; c1 < SIZE; c1++) faz_parte[c1] = -1;

	tau_rec(grafo, nro_vertices, lin, faz_parte, aux);
	free(aux);
}

// parte recursiva da funcao que calcula o tau inverso
void tau_inv_rec(int grafo[SIZE][SIZE], int nro_vertices, int col, int faz_parte[SIZE], int *aux)
{
	int lin, i;
	
	if(faz_parte[0] == -1) {
		faz_parte[0] = col;
		i = *aux;
		i++;
		*aux = i;
	}

	for(lin = 0; lin < nro_vertices; lin++) {
		if((grafo[lin][col] == 1)&&(!pertence(lin, faz_parte))) {
			i = *aux;
			faz_parte[i] = lin;
			i++;
			*aux = i;	
			tau_inv_rec(grafo, nro_vertices, lin, faz_parte, aux);
		}
	}
	return;
}

// parte nao-recursiva (inicializacao) da funcao que calcula o tau inverso
void tau_inv(int grafo[SIZE][SIZE], int nro_vertices, int col, int faz_parte[SIZE])
{
	int *aux, c1;

	aux = (int *)malloc(sizeof(int));
	*aux = 0;
	for(c1 = 0; c1 < SIZE; c1++) faz_parte[c1] = -1;

	tau_inv_rec(grafo, nro_vertices, col, faz_parte, aux);
	free(aux);
}

// calcula a interseccao entre dois arrays
void interseccao(int vai[SIZE], int vem[SIZE], int intersect[SIZE], int nro_vertices)
{
	int c1, c2, i;

	for(c1 = 0; c1 < nro_vertices; c1++) intersect[c1] = -1;

	i = 0;
	for(c1 = 0; c1 < nro_vertices; c1++) {
		for(c2 = 0; c2 < nro_vertices; c2++) {
			if(vai[c1] == vem[c2]) {
				intersect[i] = vai[c1];
				i++;
			}
		}
	}
	return;
}

// tira do grafo os componetes maximais fortemente conexos jah encontrados
void limpa_grafo(int grafo[SIZE][SIZE], int ind[SIZE], int nro_vertices)
{
	int c1, c2, i;

	for(c1 = 0; c1 < nro_vertices; c1++) {
		i = ind[c1];
		for(c2 = 0; c2 < nro_vertices; c2++) {
			grafo[i][c2] = grafo[i][c2] = 0;
		}
	}
	return;
}

int main()
{
	int grafo[SIZE][SIZE], inicial, nro_vertices, vem[SIZE], vai[SIZE], ind[SIZE], jah[SIZE];
	int c1, c2;
	char filename[100];

	printf("Digite o nome do arquivo de entrada:");
	scanf("%s", filename);
	get_graph(filename, grafo, &nro_vertices);

	printf("\n\nConjuntos Maximais Fortemente Conexos:\n");

	for(c1 = 0; c1 < SIZE; c1++) jah[c1] = -1; //  "zera" componentes jah encontrados
	for(inicial = 0;; inicial++) {
		
		while(pertence(inicial, jah)) inicial++;
		if(inicial == nro_vertices) break;

		tau(grafo, nro_vertices, inicial, vai);	
		tau_inv(grafo, nro_vertices, inicial, vem);	
		interseccao(vai, vem, ind, nro_vertices);

		for(c2 = 0; jah[c2] != -1; c2++);
		for(c1 = 0; c1 < nro_vertices; c1++) if(ind[c1] != -1) {
			printf("%d ", ind[c1]);
			jah[c2+c1] = ind[c1];
		}
		printf("\n");

		limpa_grafo(grafo, ind, nro_vertices);
	}

	fclose(out);
	getchar();
	getchar();
	return 0;
}
