#include <iostream>
#include <assert.h>
#include <limits.h>
#include <string.h>
using namespace std;

typedef struct{ 
    int fate, cancel, id;
} Requests;

typedef struct{
    int **Grafo;
} Grafo;

Grafo *criaGrafo(int V){                     // tentei fazer por matriz booleana antes mas dava muito trabalho ai ficou essa coisa feia ai
    Grafo *graph = new Grafo;                    
    graph->Grafo = (int**) malloc(V * sizeof(int*)); 
    for(int i=0; i<V; i++) 
        graph->Grafo[i] = (int*) calloc(V, sizeof(int));

    return graph;      // girlfriend???
}

int minimum(int distances[], bool visitados[], int V){

    int menor = INT_MAX, menor_index;
 
    for (int v = 0; v < V; v++)
        if (visitados[v] == false && distances[v] <= menor)
            menor = distances[v], menor_index = v;
 
    return menor_index;
}

void dijkstra(int **graph, int root, int V, int **result){
    int distances[V];
    bool visitados[V];
 
    for(int i = 0; i < V; i++){
        distances[i] = 999999;
        visitados[i] = false;
    }
    distances[root] = 0;
 
    for(int count = 0; count < V; count++){
        int u = minimum(distances, visitados, V);

        visitados[u] = true;

        for(int v = 0; v < V; v++){
            if (!visitados[v] && graph[u][v] && distances[u] != INT_MAX && distances[u] + graph[u][v] < distances[v])
                distances[v] = distances[u] + graph[u][v];
        }
    }

    for(int i = 0; i < V; i++){
        (*result)[i] = distances[i];
    }
}



int main(void){
    int V, E, N, M;
    int A, B, L;
    int IDrequest, fate, IDeliverer;
    int aux_N_requests = 0, N_requests = 0, N_cancels = 0;
    int less, idx;
    char command[4];
    int max;
    scanf("%d %d %d %d", &V, &E, &N, &M);
    
    int distFinal[N];
    Grafo *grafo = criaGrafo(V); 
    Requests *demmands = NULL; 

    int **distances = (int **)calloc(N, sizeof(int*));

    for (int i = 0; i < E; i++){
        distances[i] = (int *)calloc(V, sizeof(int));      // criando a matriz pra relacionar a distancia de cada vertice pra todos os pontos
    }

    for(int i=0; i < E; i++){
        scanf("%d %d %d", &A, &B, &L);
        grafo->Grafo[A][B] = L;
        grafo->Grafo[B][A] = L;              // botando os valores no grafo
    }

    int StorePosition[N];
    int DelivererPosition[M];

    for(int i = 0; i < N; i++){  
        scanf("%d", &StorePosition[i]); 
    }
    for(int i = 0; i < M; i++){
        DelivererPosition[i] = StorePosition[0];
    }
    for(int i = 0; i < N; i++){
        dijkstra(grafo->Grafo, StorePosition[i], V, &distances[i]);           // inserindo as distancias minimas de cada ponto pra nao dar aquele TLE de merda
    }

    while(strcmp(command, "END") != 0){
        scanf(" %s", command);
        if((strcmp(command, "NEW")) == 0){ 
            scanf("%d %d", &IDrequest, &fate);
            N_requests++;

            if(demmands == NULL){ 
                demmands = (Requests*) calloc(1, sizeof(Requests));
                demmands[0].id = IDrequest;
                demmands[0].fate = fate;
                demmands[0].cancel = 0;
            }
            else{ 
                demmands = (Requests*) realloc(demmands, sizeof(Requests)*N_requests);
                demmands[N_requests-1].id = IDrequest;
                demmands[N_requests-1].fate = fate;
                demmands[N_requests-1].cancel = 0; 
            }
            printf("+%d %d\n", IDrequest, N_requests - N_cancels);
        }
        else if(strcmp(command, "CEL") == 0){ 
            scanf("%d", &IDrequest);
            N_cancels++;
            demmands[IDrequest].cancel = 1; 
            printf("-%d %d\n", IDrequest, N_requests - N_cancels);
        }
        else if(strcmp(command, "DLV") == 0){ 
            scanf("%d", &IDeliverer);
            N_cancels++;
            max = 99999;
            while(demmands[aux_N_requests].cancel == 1)
            aux_N_requests++;
            
            for(int i = 0; i < N; i++){
               distFinal[i] = distances[i][DelivererPosition[IDeliverer]] + distances[i][demmands[aux_N_requests].fate];
            }
            for(int i = 0; i < N; i++){
                if(distFinal[i] < max){
                    max = distFinal[i];
                    idx = i;
                }
            }
            demmands[aux_N_requests].cancel = 1;
            printf("%d %d %d %d %d\n", demmands[aux_N_requests].id, DelivererPosition[IDeliverer], StorePosition[idx], demmands[aux_N_requests].fate, max);
            DelivererPosition[IDeliverer] = demmands[aux_N_requests].fate;
        }
    }

    return 0;
}