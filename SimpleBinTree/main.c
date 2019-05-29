#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Nodes {
    int value;                       /// Valor do nodo
    unsigned short nOfEqualNodes;    /// Caso tenha outros nodos iguais. Zero significa que n�o h� outras c�pias do mesmo nodo,
    								 /// 1 significa que h� uma c�pia do nodo, ou seja, foram inseridos dois valores iguais
    struct Nodes *right, *left;      /// Nodos direito e esquerdo, sendo o valor do nodo esquerdo menor
                                     /// e o valor do direito maior
} Node;

/**
 * Cria um nodo com o valor especificado.
 *
 * @param value Valor do nodo que será criado
 * @return Node|NULL
 */
Node *createNode(int value, int nOfEqualNodes){
    Node *newNode;
    newNode = malloc(sizeof(Node));
    if(newNode == NULL || nOfEqualNodes < 0) return NULL;
    // Retorna NULL se não teve espaço em memória ou se foi passado um número de nodos iguais inválido

    newNode->value = value;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->nOfEqualNodes = nOfEqualNodes;

    return newNode;
}

/**
 * O(n) descrito na fun��o 'insert'
 *
 * Insere valores na árvore.
 * Se o valor for menor que o valor do nodo, é inserido à esquerda, se for maior
 * é inserido à direita e se for igual é incrementado ao "nOfEqualNodes" do nodo.
 *
 * @param value Valor a ser inserido
 * @param node Nodo onde deve ser checado o valor
 * @param nOfEqualNodes numero de copias a serem inseridas
 * @return Node|NULL
 */
Node *insertNValues(int value, Node *node, int nOfEqualNodes){
    if(nOfEqualNodes < 0) { return NULL; }
    if(node == NULL) return createNode(value, nOfEqualNodes); // Se um pai não foi passado, retorna o novo nodo

    if(node->value > value) {
        node->left = insertNValues(value, node->left, nOfEqualNodes);
    }
    else if(node->value < value) {
        node->right = insertNValues(value, node->right, nOfEqualNodes);
    }
    else {
        node->nOfEqualNodes += nOfEqualNodes + 1;
    }
    return node;
}

/**
 * O(n), tal que o pior caso � o que os valores foram inseridos de forma ordenada do menor pro maior ou do maior pro menor, 
 * criando praticamente uma estrutura de lista.
 *
 * Insere um valor sem cópias na árvore
 *
 * @param value
 * @param node
 * @return
 */
Node *insert(int value, Node *node){
    return insertNValues(value, node, 0);
}

/**
 * O(n) descrito na funcao 'removeNode'
 * Remove N cópias do valor na árvore. Se não houver cópias remove o nodo inteiro.
 *
 * @param value valor a ser inserido
 * @param node o nodo a ser analizado
 * @param nOfEqualNodes numero de copias a ser removida
 * @return Node|NULL
 */
Node *removeNNodes(int value, Node *node, int nOfEqualNodes){
    if(node == NULL) { return NULL; }
    if(node->value > value) {
        node->left = removeNNodes(value, node->left, nOfEqualNodes);
    }
    else if(node->value < value) {
        node->right = removeNNodes(value, node->right, nOfEqualNodes);
    }
    else {
        //Se achou um valor igual
        if(node->nOfEqualNodes > nOfEqualNodes) {
        	printf("\nRemoveu %d copia(s) do nodo %d", node->nOfEqualNodes, node->value);
            node->nOfEqualNodes -= nOfEqualNodes + 1;
            return node;
        }
        Node *aux, *preAux;
        if(node->right == NULL) {
            aux = node->left;
        }
        else if(node->left == NULL) {
            aux = node->right;
        }
        else {
            aux = node->right;
            preAux = aux;
            while(aux->left != NULL) {
                preAux = aux;
                aux = aux->left;
            }
            preAux->left = aux->right;
            aux->left = node->left;
            aux->right = node->right;
        }
        printf("\nRemoveu nodo %d", node->value);
        free(node);
        return aux;
    }
}

/**
 * O(n), tal que o pior caso � o que os valores foram inseridos de forma ordenada do menor pro maior ou do maior pro menor, 
 * criando praticamente uma estrutura de lista, e o valor a ser removido � a "folha" dessa �rvore linear.
 *
 * Remove uma cópia do valor na árvore. Se não houver cópias remove o nodo inteiro.
 *
 * @param value
 * @param node
 * @return Node|NULL
 */
Node *removeNode(int value, Node *node){
    return removeNNodes(value, node, 0);
}

/**
 * O(n), pois a impress�o sempre ser� feita em todos elementos da lista
 *
 * Imprime na tela os valores em ordem esquerda -> raiz -> direita
 * Dessa forma, em uma árvore de busca binária, imprime os valores em ordem crescente
 *
 * @param node
 */
void printInOrder(Node *node){
	int i;
    if(node == NULL) { return; }
    printInOrder(node->left);
    for(i = 0; i <= node->nOfEqualNodes; i++) {
        printf("%d ", node->value);
    }
    printInOrder(node->right);
}

/**
 * O(n), pois a impress�o sempre ser� feita em todos elementos da lista
 *
 * Imprime na tela os valores em ordem raiz -> esquerda -> direita
 *
 * @param node
 */
void printPreOrder(Node *node){
	int i;
    if(node == NULL) { return; }
    for(i = 0; i <= node->nOfEqualNodes; i++) {
        printf("%d ", node->value);
    }
    printPreOrder(node->left);
    printPreOrder(node->right);
}

/**
 * O(n), pois a impress�o sempre ser� feita em todos elementos da lista
 *
 * Imprime na tela os valores em ordem esquerda -> direita -> raiz
 *
 * @param node
 */
void printPostOrder(Node *node){
	int i;
    if(node == NULL) { return; }
    printPostOrder(node->left);
    printPostOrder(node->right);
    for(i = 0; i <= node->nOfEqualNodes; i++) {
        printf("%d ", node->value);
    }
}

/**
 * O(n), pois deve percorrer todo o vetor
 *
 * Transforma um vetor em uma árvore binária
 *
 * @param arr O vetor que será transformado em árvore binária
 * @param size Tamanho do vetor
 * @return Node|NULL
 */
Node *arrayToBinTree(int arr[], size_t size) {
	size_t i;
    Node *root = NULL;
    for(i = 0; i < size; i++) {
        root = insert(arr[i], root);
    }
    return root;
}

int main() {
    int arr[] = {2, 3, 5, 5, 7};
    size_t len = sizeof(arr)/ sizeof(arr[0]);
    Node *root;

    root = arrayToBinTree(arr, len);

    printf("Pos ordem: ");
    printPostOrder(root);
    printf("\nPre ordem: ");
    printPreOrder(root);
    printf("\nEm ordem: ");
    printInOrder(root);
    root = removeNode(5, root);
    printf("\nEm ordem: ");
    printInOrder(root);
    root = removeNode(5, root);
    printf("\nEm ordem: ");
    printInOrder(root);
    
    


    return 0;
}
