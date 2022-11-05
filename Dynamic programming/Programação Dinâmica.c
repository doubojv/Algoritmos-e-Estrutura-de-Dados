#include <stdio.h>
#include <limits.h>

/* int mai(int x, int j){
    if(x > y){
        return x;
    }
    if(y > x){
        return y;
    }
} */

void DynamicProgramm(int v, int c, int C[], int V[], int Matriz[c+1][v+1]){
    
    for (int i = 1; i <= c; i++){
        for (int j = 1; j <= v; j++){
            if ((j >= i)  && ((v - (c - i)) >= j)){
                if (i == 1){
                    if ((C[i - 1] * V[j - 1]) > Matriz[i][j - 1])
                        Matriz[i][j] = (C[i - 1] * V[j - 1]);
                    else
                        Matriz[i][j] = Matriz[i][j - 1];
                    }
                    else{
                        if (((C[i - 1] * V[j - 1]) + Matriz[i-1][j-1]) > Matriz[i][j - 1])
                            Matriz[i][j] = ((C[i - 1] * V[j - 1]) + Matriz[i - 1][j - 1]);
                        else
                            Matriz[i][j] = Matriz[i][j - 1];
                    }
                }
                else{
                    Matriz[i][j] = INT_MIN;
            }            
        }
    }
}

int main(){

int v = 0;
int c = 0;


while(scanf("%d", &v) != EOF){
    scanf("%d", &c);
int auxv = v;
int auxc = c;
int aux_val = 0;
int V[v], C[c];  
int Matriz[c+1][v+1];
int aux[c];           // vetor que vai salvar as soluções parciais
Matriz[0][v] = INT_MIN;
Matriz[c][0] = INT_MIN;         // colocando - infinito 

 for(int i = 0 ; i < v ; i++){      // zerando os vetores
    V[i] = 0;
} 
for(int i = 0 ; i < c ; i++){
    C[i] = 0;
}

for(int j = 0 ; j < v ; j++){      // "zerando" a primeira linha
    if(j < v)
    scanf("%d", &V[j]);
    Matriz[0][j] = INT_MIN;
}

for(int i = 0 ; i < c ; i++){    // "zerando" a primeira coluna
    if(i < c)
    scanf("%d", &C[i]);
    Matriz[i][0] = INT_MIN;
}

  DynamicProgramm(auxv, auxc, C, V, Matriz);    

   
    for(int i = c; i > 0; i--){
        for (int j = v - aux_val; j > 0; j--){
            if (Matriz[i][j] != Matriz[i][j-1]){
                aux[i-1] = --j;                   // salvando os index escolhidos pra printar + tarde
                aux_val++;
                j = 0; 
                }
                else{
                aux_val++;
                }
            }
        }
        printf("%d\n", Matriz[c][v]);
        for (int i = 0; i < c; i++){
            if (i != c - 1){
                printf("%d ", aux[i]);
            }
            else{
                printf("%d", aux[i]);     // demorei tanto pra pensar nesse else sem espaço no print
            }
        }
        printf("\n\n");
    }

    return 0;
}