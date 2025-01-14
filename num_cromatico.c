#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int contaLinhas(char *nomeFicheiro){
    FILE *f = fopen(nomeFicheiro, "r");

    if(f == NULL){
        printf("\nErro na abertura do ficheiro em contaLinhas()");
        return -1;
    }

    char buff[256];
    int linhas = 0;

    fseek(f, 0, SEEK_SET);

    while(fgets(buff, sizeof(buff), f)){
        linhas++;
    }

    fclose(f);

    return linhas;
}

void ordenaSequenciaBolha(int **sequenciaGraus, int tamanho);

void criarCores(int **matrizAdjunta, int **sequenciaGraus, int tamanho);

void algGuloso(int **matrizAdjunta, int **sequenciaGraus, int tamanho);

int main(){

    printf("\nPrograma criado por Junior Coelho\n");
    printf("\n#################################\n");
    
    int linhas = contaLinhas("matriz_adjunta.txt");

    //printf("\nNumero de linhas: %d\n", linhas);

    int n=0;

    int **matrizAdjunta;
    matrizAdjunta = (int **) malloc(linhas * sizeof(int *));
    for(n=0; n<linhas; n++){
        matrizAdjunta[n] = (int *) malloc(linhas * sizeof(int));
    }

    n=0;

    FILE *p = fopen("matriz_adjunta.txt", "r");

    if(p == NULL){
        printf("\nErro na abertura do ficheiro em main()\n");
        system("pause");
        return -1;
    }

    fseek(p, 0, SEEK_SET);

    while(!feof(p)){

        unsigned long pos = ftell(p);
        fflush(p);
        fseek(p, pos, SEEK_SET);

        int i;

        for(i=0; i<linhas; i++){
            fscanf(p, "%d ", &matrizAdjunta[n][i]);
            //printf("\nNumero de colunas nesta linha: %d", i+1);
        }

        if(i != linhas){
            printf("\nErro: a matriz nao e quadrada.\n");
            system("pause");
            return -1;
        }

        //printf("\n");

        n++;
    }

    fclose(p);

    int i, j;

    bool isSimetric = true;

    for(i=0; i<linhas; i++){
        for(j=0; j<linhas; j++){
            if(matrizAdjunta[i][j] != matrizAdjunta[j][i]){
                isSimetric = false;
                break;
            }
        }
    }

    if(isSimetric){
        //printf("\n\nA matriz adjunta e simetrica.\n");
    }
    else{
        printf("\nErro: a matriz adjunta nao e simetrica.\n");
        system("pause");
        return -1;
    }

    //int sequenciaGraus[linhas][2]; //ALOCAR MATRIZ COM MALLOC, NAO PODE SER ESTATICA SE NAO ESTIVER DEFINIDA NO INICIO

    int op;
    printf("\n--- MENU ---");
    printf("\n1. Algoritmo gluoso");
    printf("\n2. Algoritmo de Welsh Powell");
    
    do{
        printf("\nInsira opcao: ");
        scanf("%d", &op);
    }while((op < 1) || (op > 2));

    printf("\n");

    int k;

    int **sequenciaGraus;
    sequenciaGraus = (int **) malloc(linhas * sizeof(int *));
    for(k=0; k<linhas; k++){
        sequenciaGraus[k] = (int *) malloc(3 * sizeof(int));
    }

    k = 0;

    for(k=0; k<linhas; k++){
        sequenciaGraus[k][0] = k+1;
        sequenciaGraus[k][1] = 0;
    }

    int l, m;

    for(l=0; l<linhas; l++){
        for(m=0; m<linhas; m++){
            sequenciaGraus[l][1] += matrizAdjunta[l][m];
        }
    }

    int a;

    if(op == 1){
        algGuloso(matrizAdjunta, sequenciaGraus, linhas);
    }
    else{
        if(op == 2){
            ordenaSequenciaBolha(sequenciaGraus, linhas);
            criarCores(matrizAdjunta, sequenciaGraus, linhas);
        }
    }

    a = 0;
    int numCrom = 0;

    printf("\n\nDistribuir cores:\n");
    for(a=0; a<linhas; a++){
        printf("Letra %d tem cor %d\n", sequenciaGraus[a][0], sequenciaGraus[a][2]);
        if(sequenciaGraus[a][2] > numCrom){
            numCrom = sequenciaGraus[a][2];
        }
    }

    a = 0;

    printf("\n--> Numero cromatico: %d\n\n", numCrom);

    system("pause");

    return -1;
}

void criarCores(int **matrizAdjunta, int **sequenciaGraus, int tamanho){
    int i, j;
    int corNum = 1;

    for(i=0; i<tamanho; i++){
        sequenciaGraus[i][2] = 1;
    }

    i=0;

    for(i=1; i<tamanho; i++){
        for(j=0; j<i; j++){
            //printf("\nmatrizAdjunta[%d][%d] = %d", (sequenciaGraus[i][0])-1, (sequenciaGraus[j][0])-1, matrizAdjunta[(sequenciaGraus[i][0])-1][(sequenciaGraus[j][0])-1]);
        
            //printf("\n\nVou verificar a entrada %d %d", sequenciaGraus[i][0], sequenciaGraus[j][0]);
            //printf("\ni = %d; j = %d", i, j);

            if(matrizAdjunta[(sequenciaGraus[i][0])-1][(sequenciaGraus[j][0])-1] > 0){
                //printf("\nLetras %d e %d estao conectados", sequenciaGraus[i][0], sequenciaGraus[j][0]);
                
                if(sequenciaGraus[i][2] == sequenciaGraus[j][2]){
                    sequenciaGraus[i][2]++;
                }

                /*
                while(sequenciaGraus[i][2] <= sequenciaGraus[j][2]){
                    printf("\nA letra %d tinha cor %d", sequenciaGraus[i][0], sequenciaGraus[i][2]);
                    sequenciaGraus[i][2]++;
                    printf("\nA letra %d tem cor %d", sequenciaGraus[i][0], sequenciaGraus[i][2]);
                }
                */
            }

            //printf("\n");
        }

        //printf("\n");

        corNum = 1;
    }
}

void algGuloso(int **matrizAdjunta, int **sequenciaGraus, int tamanho){
    int i = 0, j = 0;
    //int corNum = 1;

    for(i=0; i<tamanho; i++){
        sequenciaGraus[i][2] = 1;
    }

    i=0;

    bool increase_j = true;

    //bool searchEnabled = true;

    for(i=1; i<tamanho; i++){
        while(j<i){
            increase_j = true;

            //printf("\nmatrizAdjunta[%d][%d] = %d", (sequenciaGraus[i][0])-1, (sequenciaGraus[j][0])-1, matrizAdjunta[(sequenciaGraus[i][0])-1][(sequenciaGraus[j][0])-1]);
            
            if(matrizAdjunta[(sequenciaGraus[i][0])-1][(sequenciaGraus[j][0])-1] > 0){
                //printf("\nLetras %d e %d estao conectados", sequenciaGraus[i][0], sequenciaGraus[j][0]);

                if(sequenciaGraus[i][2] == sequenciaGraus[j][2]){
                    sequenciaGraus[i][2]++;
                    increase_j = false;
                }
            }
            if(increase_j){
                j++;
            }
            else{
                j=0;
            }
            //printf("\n");
        }
        j=0;

        //printf("\n");
    }
}

void ordenaSequenciaBolha(int **sequenciaGraus, int tamanho){
    int i;
    bool isOrdered = false;

    while(!isOrdered){
        isOrdered = true;

        for(i=0; i<(tamanho-1); i++){
            if(sequenciaGraus[i][1] < sequenciaGraus[i+1][1]){

                isOrdered = false;

                int temp1, temp2;

                temp1 = sequenciaGraus[i+1][0];
                temp2 = sequenciaGraus[i+1][1];

                sequenciaGraus[i+1][0] = sequenciaGraus[i][0];
                sequenciaGraus[i+1][1] = sequenciaGraus[i][1];

                sequenciaGraus[i][0] = temp1;
                sequenciaGraus[i][1] = temp2;
            }
        }
    }

    int a;

    printf("\n\nOrdenacao descrescente dos graus:");

    for(a=0; a<tamanho; a++){
        printf("\nLetra %d tem grau %d", sequenciaGraus[a][0], sequenciaGraus[a][1]);
    }
}
