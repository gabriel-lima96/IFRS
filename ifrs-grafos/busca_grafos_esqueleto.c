/** Instituto Federal do Rio Grande do Sul - Prof. Renan Guedes Maidana
*	Trabalho 2 - Estrutura de Dados 2
*	
*	Busca em grafos: Custo mínimo e Dijkstra
*
*	Aluno: Gabriel Alves de Lima
*	Data: 06/07/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITE 200	// Definição de número "infinito" para montar a matriz de custos
#define MAX_NODE 10		// Número máximo de nodos para criação das matrizes de custo e adjacência

// Declaração das matrizes de custo e adjacência
int adj[MAX_NODE][MAX_NODE];
int cost[MAX_NODE][MAX_NODE];

/** Função para ler a representação do grafo de um arquivo de texto
O grafo é descrito da seguinte maneira, por exemplo:

2
node:0
1,10
node:1

Onde a primeira linha é o numero total de nós. O restante da linhas 
detalha o nos em "node:x", e abaixo quais são seus sucessores e pesos.

Ex: Abaixo, o no 0 possui um sucessor no nodo 1, com peso de comunicacao de 10. 
Já o no 1 nao possui sucessores.
node:0
1,10
node:1

Você deve implementar o código que irá realizar o cálculo das matrizes de custo e adjacência,
conforme dados presentes no arquivo.
*/
int loadGraph(char* filename){
	// Iremos carregar o grafo a partir de um arquivo de texto estruturado, conforme
	// estrutura indicada acima
	FILE *f = fopen(filename, "rt");
	char line[20];
	
	if (f == NULL){
	    printf("Problemas na leitura do arquivo %s\n", filename);
	    return -1;
	}
	
	// Consideramos que a primeira linha do arquivo é o número de nodos
	fgets(line, 100, f);  // o 'fgets' lê até 99 caracteres, ou até o '\n'
	int n_nodes = atoi(line);
		
	// Inicializamos a matriz de adjacência e a lista de nodos visitados com zeros (até o número de nós especificado no arquivo)
	// Utiliza-se somente parte da matriz total de MAX_NODE vs MAX_NODE
	int i, j;
	for(i=0; i<n_nodes; i++){
		for(j=0; j<n_nodes; j++){
			adj[i][j] = 0;
			cost[i][j] = INFINITE;
		}
	}
	
	// VOCÊ DEVE: Continuar lendo o arquivo até o final e calcular matrizes de adjacência e custo
	int fetch;
	while(fgets(line, 100, f) != NULL){
	    printf("Leu %s", line);
	}
	// Fecha o arquivo de texto do grafo
	fclose(f);
	
	// Retorna o numero de nodos
	return n_nodes;
}

/** VOCÊ DEVE: Implementar o algoritmo de busca em grafos por custo mínimo
* 
* Parâmetros: 
*	n_nodes - numero total de nodos no grafo
*	start - nodo inicial para busca
*	goal  - nodo objetivo (destino) da busca
*
* Saída:
*	O caminho no grafo, do "start" até o "goal", segundo o algoritmo de busca em grafos por custo mínimo
*/
void custo_minimo(int n_nodes, int start, int goal){}


/** VOCÊ DEVE: Implementar o algoritmo de Dijkstra para busca em grafos
*
* Parâmetros: 
*	n_nodes - numero total de nodos no grafo
*	start - nodo inicial para busca
*	goal  - nodo objetivo (destino) da busca
*
* Saída:
*	O caminho no grafo, do "start" até o "goal", segundo o algoritmo de Dijkstra
*/
void dijkstra(int n_nodes, int start, int goal){}

// Função main
int main(){
	// Obtém grafo do arquivo "grafo.txt", já calculando as matrizes
	int n_nodes = loadGraph("grafo.txt");
	
	/* ----- Imprimir aqui a matriz de adjacências ----- */
	
	/* ----- Imprimir aqui a matriz de custo ----- */
	
	// Busca no grafo inicia no nodo 0, com objetivo de chegar no nodo 3
	int start=0, goal=3;
	
	// Chamar aqui a procedimento que obtém/imprime o caminho pelo algoritmo GBFS
	
	// Chamar aqui o procedimento que obtém/imprime o caminho pelo algoritmo de Dijkstra	
	
	// Fim! Boas férias!
	return 0;
}
