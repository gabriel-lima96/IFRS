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
    printf("\nMatriz de adjecencia:");
    for(i=0; i<n_nodes; i++){
        printf("\n");
        for(j=0; j<n_nodes; j++){
            printf("%4d ", adj[i][j]);
        }
    }

    printf("\n");

    printf("\nMatriz de custo:");
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
void dijkstra(int n_nodes, int start, int goal) {
    if (n_nodes < 1) { return; }
    if (n_nodes == 1 || start == goal) {
        printf("%d", start);
        return;
    }
    /* Inicialização das variáveis */
    int menorCusto[n_nodes];        /// @var int[] menorCusto Array que armazena o menor custo para cada nodo
    int precedentes[n_nodes];       /// @var int[] precedentes Array que armazena o o nodo anterior de acordo com o menor custo
    int visitados[n_nodes];         /// @var int[] visitados Array que armazena um boolean (0 ou 1) indicando se o novo já foi visitado
    // Inicializa as informações referentes ao primeiro nodo
    menorCusto[0] = 0;
    precedentes[0] = 0;
    visitados[0] = 0;
    for (int i = 1; i < n_nodes; i++) {
        // Inicializa custos, precedentes e se foi visitado nos outros nodos
        menorCusto[i] = INFINITE;
        precedentes[i] = -1;
        visitados[i] = 0;
    }

    int pivo = 0;
    int menor;
    while (precedentes[0] == 0) {
        menor = -1;
        visitados[pivo] = 1;
        // Procura todos nodos adjecentes e calcula os custos
        for (int i = 0; i < n_nodes; i++) {
            // Se não é um nodo adjecente ou se foi visitado, vai pro próximo
            if (!adj[pivo][i]) { continue; }
            // Se o resultado do calculo de menor custo entre esse precedente for menor que o menor custo encontrado
            // até então para o nodo 'i', substitui no 'menorCusto' e no 'precedentes'
            if (cost[pivo][i] + menorCusto[pivo] < menorCusto[i]) {
                menorCusto[i] = cost[pivo][i] + menorCusto[pivo];
                precedentes[i] = pivo;
            }
            //  Verifica se esse é o próximo nodo que deve ser visitado
            if (menorCusto[i] > menor && !visitados[i]) {
                menor = i;
            }
        }
        // Se verificou todos nodos adjecentes
        if (menor == -1) {
            if (pivo == precedentes[pivo]) {
                // Percorreu o grafo inteiro e voltou ao start
                break;
            }
            // Volta para o nodo anterior
            pivo = precedentes[pivo];
        }
            // Se ainda há um nodo que ainda não foi explorado
        else {
            pivo = menor;
        }
    }

    // Imprime o caminho:
    if (precedentes[goal] == -1) {
        printf("Não encontrou o destino\n");
        return;
    }
    pivo = goal;
    int caminho[n_nodes];
    int count = 0;
    // Monta o array com os caminhos
    while (precedentes[pivo] != pivo) {
        caminho[count++] = pivo;
        pivo = precedentes[pivo];
    }
    caminho[count] = precedentes[pivo];
    // E, finalmente, imprime os caminhos
    for (int i = count; i > 0; i--) {
        printf("%d -> ", caminho[i]);
    }
    printf("%d", caminho[0]);
    fflush(stdout); // Só pra garantir
}

// Função main
int main(int argc, char** args){
    // Obtém grafo do arquivo "grafo.txt", já calculando as matrizes
    int n_nodes = loadGraph("grafo3.txt");

    _imprimirMatrizes(n_nodes);
    printf("\n");

    // Busca no grafo inicia no nodo 0, com objetivo de chegar no nodo 3
    int start = 0, goal = 3; //grafo.txt
    //int start = 0, goal=3; //grafo2.txt

    printf("\nCusto mínimo: \n");
    custo_minimo(n_nodes, start, goal);

    printf("\n");
    printf("\nDijkstra: \n");
    dijkstra(n_nodes, start, goal);

    // Fim! Boas férias!
    // Valeu fessor!
    return 0;
}
