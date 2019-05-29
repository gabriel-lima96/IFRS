#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Nodes {
    int value;                       /// Valor do nodo
    unsigned short nOfEqualNodes;    /// Caso tenha outros nodos iguais. COMEÇA EM ZERO
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
 * Insere valores na árvore.
 * Se o valor for menor que o valor do nodo, é inserido à esquerda, se for maior
 * é inserido à direita e se for igual é adicionado ao "nOfEqualNodes" do nodo.
 *
 * @param value Valor a ser inserido
 * @param node Nodo onde deve ser checado o valor
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
        node->nOfEqualNodes += nOfEqualNodes;
    }
    return node;
}

/**
 * Insere um valor sem cópias na árvore
 *
 * @param value
 * @param node
 * @return
 */
Node *insert(int value, Node *node){
    return insertNValues(value, node, 0);
}

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
            node->nOfEqualNodes -= nOfEqualNodes;
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
        printf("Removeu");
        free(node);
        return aux;
    }
}

/**
 * Remove uma cópia do valor na árvore. Se não houver cópias remove o nodo inteiro se for encontrado no valor.
 * Se não for encontrado, retorna 0, senão 1 (boolean)
 *
 * @param value
 * @param node
 * @return
 */
Node *removeNode(int value, Node *node){
    return removeNNodes(value, node, 1);
}

/**
 * Imprime na tela os valores em ordem esquerda -> raiz -> direita
 * Dessa forma, em uma árvore de busca binária, imprime os valores em ordem crescente
 *
 * @param node
 */
void printInOrder(Node *node){
    if(node == NULL) { return; }
    printInOrder(node->left);
    for(int i = 0; i <= node->nOfEqualNodes; i++) {
        printf("%d ", node->value);
    }
    printInOrder(node->right);
}

/**
 * Imprime na tela os valores em ordem raiz -> esquerda -> direita
 *
 * @param node
 */
void printPreOrder(Node *node){
    if(node == NULL) { return; }
    for(int i = 0; i <= node->nOfEqualNodes; i++) {
        printf("%d ", node->value);
    }
    printPreOrder(node->left);
    printPreOrder(node->right);
}

/**
 * Imprime na tela os valores em ordem esquerda -> direita -> raiz
 *
 * @param node
 */
void printPostOrder(Node *node){
    if(node == NULL) { return; }
    printPostOrder(node->left);
    printPostOrder(node->right);
    for(int i = 0; i <= node->nOfEqualNodes; i++) {
        printf("%d ", node->value);
    }
}

/**
 * Transforma um vetor em uma árvore binária
 *
 * @param arr O vetor que será transformado em árvore binária
 * @param size Tamanho do vetor
 * @return Node|NULL
 */
Node *arrayToBinTree(int arr[], size_t size) {
    Node *root = NULL;
    for(size_t i = 0; i < size; i++) {
        root = insert(arr[i], root);
    }
    return root;
}

int main() {
    int arr[] = {2, 3, 5, 7};
    size_t len = sizeof(arr)/ sizeof(arr[0]);
    Node *root;

    root = arrayToBinTree(arr, len);

    printf("Pós ordem: ");
    printPostOrder(root);
    printf("\nPré ordem: ");
    printPreOrder(root);
    root = removeNode(2, root);
    printf("\nEm ordem: ");
    printInOrder(root);


    return 0;
}