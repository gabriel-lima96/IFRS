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

    //  + um espaço para o NULL do final
    const size_t nodo_size = MAX_NODE/10; ///@var nodo_size Tamanho mínimo pra guardar os caracteres do nodo escritos em decimal
    char *nodo_str = malloc(nodo_size);       ///@var nodo Variável que armazena o nodo do qual as próximas linhas do arquivo se referenciam

    int nodo;
    int nodo_adj;
    int nodo_adj_custo;
    while(fgets(line, 100, f) != NULL){
        if(strstr(line, "node:") != NULL) { // Checa se é o começo de de um novo nodo
            strncpy(nodo_str, &line[5], nodo_size); // Copia o valor depois de 'nodo:' para a variavel nodo
            continue; // Se já fez o que devia, então vai pra próxima linha!
        }
        nodo = atoi(nodo_str); // Faz o 'parse' do nodo que estava em string para integer
        nodo_adj = atoi(strtok(line, ",")); // Quebra a linha em duas metades, a primeira é o nodo com o qual há uma adjecencia
        nodo_adj_custo = atoi(strtok(NULL, ",")); // A segunda metade é o custo
        adj[nodo][nodo_adj] = 1; // Altera a matriz de adjecencia com a informação nova
        cost[nodo][nodo_adj] = nodo_adj_custo; // Altera a matriz de custos com a informação nova
    }

    // Fecha o arquivo de texto do grafo
    fclose(f);

    // Retorna o numero de nodos
    return n_nodes;
}


/**
 * Imprime as matrizes de custo e adjecencia
 *
 * @param n_nodes Número de nodos
 */
void _imprimirMatrizes(int n_nodes) {
    int i, j;
    for(i=0; i<n_nodes; i++){
        printf("\n");
        for(j=0; j<n_nodes; j++){
            printf("%4d ", adj[i][j]);
        }
    }

    printf("\n");

    for(i=0; i<n_nodes; i++) {
        printf("\n");
        for (j = 0; j < n_nodes; j++) {
            printf("%4d ", cost[i][j]);
        }
    }
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
void custo_minimo(int n_nodes, int start, int goal){
    int i, j; // Pivôs
    int pos_minimo;
    start == goal ? printf("%d", start) : printf("%d -> ", start); // Firula pra não imprimir a setinha se start == goal
    for(i = start; i < n_nodes;) {
        pos_minimo = 0; // Define a posição do menor
        for(j = 0; j < n_nodes; j++) {
            if(cost[i][j] < cost[i][pos_minimo]) {
                pos_minimo = j;
            }
        }
        i = pos_minimo;
        if(i == goal) {
            printf("%d", i);
            return;
        }
        printf("%d -> ", pos_minimo);
    }
    fflush(stdout); // Dar flush no buffer do stdout só pra garantir que vai imprimir tudo
}

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
int main(int argc, char** args){
    // Obtém grafo do arquivo "grafo.txt", já calculando as matrizes
    int n_nodes = loadGraph("grafo.txt");

    /* ----- Imprimir aqui a matriz de adjacências ----- */

    /* ----- Imprimir aqui a matriz de custo ----- */

    // Busca no grafo inicia no nodo 0, com objetivo de chegar no nodo 3
    int start=0, goal=3;
    custo_minimo(n_nodes, start, goal);

    // Chamar aqui a procedimento que obtém/imprime o caminho pelo algoritmo GBFS

    // Chamar aqui o procedimento que obtém/imprime o caminho pelo algoritmo de Dijkstra

    // Fim! Boas férias!
    return 0;
}
