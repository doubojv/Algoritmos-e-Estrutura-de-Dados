#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct{
    int value;
    bool **edges;
    int grade;
    bool **contracoes;
}Graph;

typedef struct no{
    struct no *next;
    int valor;
}Fila;

typedef struct{
  Fila *head, *tail;
  int tam;
}Dota;

void destroygraph(Graph *g){
    if(g->edges == NULL){
        return;
    }
    for(int i = 0 ; i < g->value ; i++){
        if(g->edges[i]){
            free(g->edges[i]);
        }
    }
    free(g->edges);
}

Graph *criate_graph(int value){
    Graph *g = (Graph*)malloc(sizeof(*g));
    g->value = value;
    g->edges = (bool**)calloc(sizeof(bool*), g->value);
    g->contracoes = (bool**)calloc(sizeof(bool*), g->value);
    if(g->edges == NULL){
        free(g);
        return NULL;
    }
    for(int i = 0 ; i < g->value ; i++){
        g->edges[i] = (bool*)calloc(sizeof(bool), g->value);
        g->contracoes[i] = (bool*)calloc(sizeof(bool), g->value);
        if(g->edges == NULL){
            destroygraph(g);
            return NULL;
        }
    }
    return g;
}

bool has_edge(Graph *g, int A , int B){
    assert(g != NULL);
    assert(A < g->value);
    assert(B < g->value);

    return g->edges[A][B];
}

bool add_edges(Graph *g, int A , int B){
    assert(g != NULL);
    assert(A < g->value);
    assert(B < g->value);


    if(has_edge(g, A, B)){
        return false;
    }
    g->edges[A][B] = true;
    return true;
}

// inserir no final da lista
void inserirFim(Dota *lista, int valor) {
    Fila *novo = (Fila*)malloc(sizeof(Fila)); // cria um novo nó
    novo->valor = valor;
    novo->next = NULL;

    if(lista->head->next == NULL) { // lista vazia
        lista->head->next = novo;
        lista->tail = novo;
    } else { // lista não vazia
        lista->tail->next = novo;
        lista->tail = novo;
    }
    
}

int removerPrimeiroNO(Fila **head, Fila **tail) {
    int valor;
    if((*head)->next != NULL){
        valor = (*head)->next->valor;
        (*head)->next = (*head)->next->next;
    }
    if((*head)->next == NULL){
        (*tail) = NULL;
        (*head)->next = NULL;
    }
    return valor;
}

int menorCaminho(Graph *grafo, int vrtInicial, int vrtFinal, int vertices){
    int i, currentLine,u, aux_index, flag = 0;
    int NV = vertices;
    int visitados[NV];
    Fila *aux2;
    int distancia[NV];

    for(int i=0; i<NV; i++){
        distancia[i] = -1;
        visitados[i] = 0;
    }
    visitados[vrtInicial] = 1;
    Dota fila;
    fila.head = (Fila*)calloc(sizeof(Fila), 1);
    fila.tail = fila.head;

    inserirFim(&fila, vrtInicial);

    distancia[vrtInicial] = 0; 
    if(grafo->contracoes[vrtInicial][vrtFinal] == 1){
        return 0;
    }
    else{
     while(fila.head->next != NULL && flag == 0){
        u = removerPrimeiroNO(&fila.head, &fila.tail);
        for(int i = 0 ; i < vertices ; i++){
            if(grafo->edges[u][i] == 1){
                aux_index = i;
                if(distancia[aux_index] == -1 || (distancia[u] + 1 < distancia[aux_index])){
                    distancia[aux_index] = distancia[u] + 1; 
                    inserirFim(&fila, aux_index);
                    if(distancia[vrtFinal] != -1){
                        flag = 1;
                    }
                }
            }
        }
    } 
}
    return distancia[vrtFinal];
}

int contract(Graph *grafo, int vertexA, int vertexB, int vertices, int auxvertices, int **representantes){
    if ((grafo->contracoes[vertexA][vertexB] == 1) || vertexA == vertexB){
        return auxvertices;
    }
    else{
        int i;
        grafo->contracoes[vertexA][vertexB] = 1; //DEFININDO QUE OS VERTICES ESTAO CONTRAIDOS
        grafo->contracoes[vertexB][vertexA] = 1; 

        for(int i=0 ; i<vertices ; i++){
            if(grafo->contracoes[vertexA][i] == 0 && grafo->contracoes[vertexB][i] == 0){ //SE O VERTICE I NAO ESTA CONTRAIDO COM A OU B
                if(grafo->edges[vertexA][i] == 1 || grafo->edges[vertexB][i] == 1){ //SE EXISTE UMA ARESTA LIGANDO A OU B AO VERTICE I
                    grafo->edges[vertexA][i] = 1;
                    grafo->edges[vertexB][i] = 1;
                    
                }
                if(grafo->edges[i][vertexA] == 1 || grafo->edges[i][vertexB] == 1){ //SE EXISTE UMA ARESTA LIGANDO I AO VERTICE A OU B
                    grafo->edges[i][vertexA] = 1;
                    grafo->edges[i][vertexB] = 1;
                }
            }
            else{                                     // AGORA VIROU NOVOS IRMÃOS !
                grafo->edges[vertexA][i] = 0;              
                grafo->edges[vertexB][i] = 0;
                grafo->edges[i][vertexA] = 0;
                grafo->edges[i][vertexB] = 0;
            }

        }

        grafo->edges[vertexA][vertexB] = 0; //NAO EXISTE ARESTAS PARA CONTRAIDOS
        grafo->edges[vertexB][vertexA] = 0;

        grafo->edges[vertexA][vertexA] = 0; //NÃO EXISTE ARESTAS PARA SI PROPRIO
        grafo->edges[vertexB][vertexB] = 0;

        for(int i=0 ; i < vertices ; i++){
            if((grafo->contracoes[vertexA][i] == 1) && (i != vertexB)){
                for(int j = 0; j < vertices ; j++){
                    grafo->edges[i][j] = grafo->edges[vertexA][j];     // transferindo a linha para o irmão
                    if(grafo->edges[j][vertexA] == 1){
                        grafo->edges[j][i] = 1;
                    }
                    if(grafo->contracoes[vertexB][j] == 1){
                        grafo->edges[i][j] = 0;
                        grafo->edges[j][i] = 0;
                        grafo->contracoes[i][j] = 1;
                        grafo->contracoes[j][i] = 1;
                    }
                }
                grafo->contracoes[i][vertexB] = 1;
                grafo->contracoes[vertexB][i] = 1; 
                grafo->edges[i][vertexB] = 0;
                grafo->edges[vertexB][i] = 0; 
            }
            if((grafo->contracoes[vertexB][i] == 1) && (i != vertexA)){
                for(int j = 0; j<vertices; j++){    
                    grafo->edges[i][j] = grafo->edges[vertexB][j];          // transferindo a linha para o irmão
                    if(grafo->edges[j][vertexB] == 1){
                        grafo->edges[j][i] = 1;
                    }
                    if(grafo->contracoes[vertexA][j] == 1){
                        grafo->edges[i][j] = 0;
                        grafo->edges[j][i] = 0;
                        grafo->contracoes[i][j] = 1;
                        grafo->contracoes[j][i] = 1;
                    }
                } 
                grafo->contracoes[i][vertexA] = 1;
                grafo->contracoes[vertexA][i] = 1;
                grafo->edges[i][vertexA] = 0;
                grafo->edges[vertexA][i] = 0;
            } 
            grafo->contracoes[i][i] = 0;
        }   
        
        // definir representant
        int tabacudo = vertices + 1;
        
        for(int i = 0 ; i < vertices ; i++){
            if(grafo->contracoes[vertexA][i] == 1 && i < tabacudo){
                tabacudo = i;
                break;
            }
        }
        
        if(vertexA < tabacudo){
            tabacudo = vertexA;
        }

        for(int i = 0; i < vertices ; i++){
            if(grafo->contracoes[tabacudo][i] == 1){
                (*representantes)[i] = 1;   
            }
        }
        
        auxvertices--;
        return auxvertices;
    }
}

int grade_counter(Graph *grafo, int vertexA, int *representantes, int vertices){
    int counter = 0;
     
    for(int i = 0 ; i < vertices; i++){
        if(grafo->edges[vertexA][i] == 1 && representantes[i] == 0){
            counter++;
        }
    }
    return counter;
}

int main(){
    int vertex , edge, operations, grau;
    int vertex_A, vertex_B, vertex_A2, vertex_B2;
    char command[4];
    scanf("%d %d", &vertex, &edge);
    int *representantes = (int*)calloc(vertex, sizeof(int));
    Graph *grafo = criate_graph(vertex);
    int aux = edge;
    int aux2 = vertex;
    int vertice_filhodaputa = vertex;

    while(aux > 0){
        scanf("%d %d", &vertex_A, &vertex_B);
        add_edges(grafo, vertex_A, vertex_B);
        aux--;
      }
      for(int i = 0 ; i < vertex ; i++){
        for(int j = 0 ; j < vertex ; j++){
            if(grafo->edges[i][j] == 1){
                grafo->edges[j][i] = 1;
            }
        }
      }
       scanf("%d", &operations);
      while(operations > 0){
        scanf(" %s %d %d", command, &vertex_A2, &vertex_B2);
        if(strcmp(command, "DIS") == 0){
         int x = menorCaminho(grafo, vertex_A2, vertex_B2, vertex);
         printf("%d\n", x);
        }
        if(strcmp(command, "CTR")== 0){
            int y = contract(grafo, vertex_A2, vertex_B2, vertice_filhodaputa, aux2, &representantes);
            aux2 = y;
            grau = grade_counter(grafo, vertex_A2, representantes, vertex);
            printf("%d %d\n", y, grau);
        }
        operations--;
      } 

return 0;
}
