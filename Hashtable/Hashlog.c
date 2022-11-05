#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Chorei fazendo esse codigo umas 15 vezes
typedef struct
{
    int timestamp;
    unsigned endereco;
} Cliente;

int procurar_elementor(Cliente **hash, int timestamp, int *coluna, int index)
{
    int final = coluna[index] - 1;
    int inicio = 0;

    while ((inicio <= final)){

        int i = (inicio + final) / 2;

        if (hash[index][i].timestamp < timestamp){
            inicio = i + 1;
        }
        else{
            final = i - 1;
        }
        if (hash[index][i].timestamp == timestamp){
            return i;
        }
    }
    return -1;
}

int main(){
    int M, Lmax, j, qtdrodada = 0;
    char comando[4];

    scanf("%d %d", &M, &Lmax);

    Cliente aux;
    Cliente aux2;
    int *pointer2;
    Cliente **Hashtable = (Cliente **)calloc(sizeof(Cliente *), M);
    int *pointer = (int *)calloc(sizeof(int), M);

    for (int i = 0; i < M; i++){
        Hashtable[i] = (Cliente *)calloc(sizeof(Cliente), 1);
    }

    while (strcmp(comando, "END")){
        scanf(" %s", comando);

        if (!strcmp(comando, "NEW"))
        {
            scanf("%d %u", &aux.timestamp, &aux.endereco);

            if ((float)qtdrodada / M > Lmax)
            {             
                int M_antigo = M; 
                M = (2 * M) + 1;

                Cliente **Hashtable2 = (Cliente **)calloc(sizeof(Cliente *), M);
                pointer2 = (int *)calloc(sizeof(int), M);

                for (int j = 0; j < M; j++)
                {
                    Hashtable2[j] = (Cliente *)calloc(1, sizeof(Cliente)); 
                }

                for (int i = 0; i < M_antigo; i++)
                {
                    if (pointer[i] > 0)
                    {
                        for (int j = 0; j < pointer[i]; j++)
                        {
                            int index2 = Hashtable[i][j].timestamp % M;
                            Hashtable2[index2] = (Cliente *)realloc(Hashtable2[index2], sizeof(Cliente) * (pointer2[index2] + 1));
                            Hashtable2[index2][pointer2[index2]] = Hashtable[i][j]; 
                            pointer2[index2]++;
                        }
                    }
                }

                Cliente ordem;

                for (int i = 0; i < M - 1; i++)
                { 
                    for (int j = 0; j < pointer2[i] - 1; j++)
                    {
                        for (int k = 0; k < pointer2[i] - j - 1; k++)
                        {
                            if (Hashtable2[i][k].timestamp > Hashtable2[i][k + 1].timestamp)
                            {
                                ordem = Hashtable2[i][k];
                                Hashtable2[i][k] = Hashtable2[i][k + 1];
                                Hashtable2[i][k + 1] = ordem;
                            }
                        }
                    }
                }

                Cliente **copia = Hashtable;
                int *copia_pointer = pointer;

                pointer = (int *)calloc(sizeof(int), M);
                Hashtable = (Cliente **)calloc(sizeof(Cliente), M);

                pointer = pointer2;
                Hashtable = Hashtable2;

                free(copia);
                free(copia_pointer);
                /* for (int i = 0; i < M; i++)
                {
                    free(copia[i]);
                } */
            }

            int index = aux.timestamp % M;

            if (pointer[index] == 0)
            {
                Hashtable[index][0] = aux;
                pointer[index]++;
                printf("%d %d\n", index, pointer[index]);
            }
            else
            {
                Hashtable[index] = (Cliente *)realloc(Hashtable[index], sizeof(Cliente) * (pointer[index] + 1));
                Hashtable[index][pointer[index]] = aux;
                pointer[index]++;
                printf("%d %d\n", index, pointer[index]);
            }
            qtdrodada++;
        }


        if (!strcmp(comando, "QRY"))
        {
            scanf("%d", &aux.timestamp);
            int algoritmo = aux.timestamp % M;
            int funcao = procurar_elementor(Hashtable, aux.timestamp, pointer, algoritmo);
            if (funcao == -1)
            {
                printf("-1 -1\n");
            }
            else
            {
                
                printf("%u %d\n", Hashtable[algoritmo][funcao].endereco, funcao);
            }
        }
    }

    return 0;
}
