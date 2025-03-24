#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>



typedef struct Pessoa{
    long long num;
    bool markDown;
    bool ignore;

    struct Pessoa *prox;
} PESSOA;

PESSOA *CriaPessoa(long long n){

    PESSOA *novo = (PESSOA*) malloc(sizeof(PESSOA));
    novo->prox = NULL;
    novo->markDown = false;
    novo->ignore = false;
    novo->num = n;

    return novo;
}

PESSOA *AdicionaPessoa(PESSOA *head, PESSOA *novo){
    if(head == NULL){
        printf("\nErro na busca da cabeca da lista 'head' em AdicionaPessoa\n");
        return novo;
    }

    if(novo == NULL){
        printf("\nError na busca do elemdnto 'novo' da lista em AdicionaPessoa\n");
        return head;
    }

    PESSOA *temp = head;

    while(temp->prox != NULL){
        temp = temp->prox;
    }
    temp->prox = novo;

    return head;
}

void outputFilePerTime(PESSOA *head, char *fileName, long long limit){
    FILE *f = fopen(fileName, "w");

    if(f == NULL){
        printf("\nErro na abertura do ficheiro %s em outputFilePerTime\n", fileName);
        system("pause");
        exit(-1);
    }

    if(head == NULL){
        printf("\nErro na busca da cabeca da lista ligada 'head' em outputFilePerTime\n");
        system("pause");
        exit(-1);
    }

    PESSOA *temp = head;

    long long espacosLimit = (long long) log10(limit);

    while(temp != NULL){
        long long espacosNum = (long long) log10(temp->num);
        
        fprintf(f, "%lld ", temp->num);

        long long j;
        for(j=0; j<(espacosLimit-espacosNum); j++){
            fprintf(f, " ");
        }

        temp = temp->prox;
    }

    fprintf(f, "\n");
    temp = head;

    while(temp != NULL){

        if(temp->markDown){
            fprintf(f, "X ");
        }
        else{
            fprintf(f, "O ");
        }

        //long long espacosNum = (long long) log10(temp->num);
        long long j;

        for(j=0; j<(espacosLimit); j++){
            fprintf(f, " ");
        }

        temp = temp->prox;
    }

    fclose(f);
}

void markIgnore(PESSOA *head){

    if(head == NULL){
        printf("\nErro na busca da cabeca da lista 'head' em markIgnore\n");
        system("pause");
        exit(-1);
    }

    PESSOA *temp = head;
    while(temp != NULL){
        if(temp->markDown){
            temp->ignore = true;
        }

        temp = temp->prox;
    }
}

long long changeMarkDown(PESSOA *head, long long checkLimit, bool *gotSystemPauseIgnore, long long limit, int op){

    if(head == NULL){
        printf("\nErro na busca da cabeca da lista 'head' em changeMarkDown\n");
        system("pause");
        exit(-1);
    }

    PESSOA *temp = head;

    bool markDownSwitch = false;

    long long markDownCount = 0;

    long long i=0;
    //printf("\nThe limit for checking is %lld\n", checkLimit);

    for(i=0; i<checkLimit; i++){
        long long checkAt = (i % limit) + 1;

        (*gotSystemPauseIgnore) = true;

        if(temp->ignore){
            if(i == (checkLimit-1)){
                printf("\n%lld ja foi eliminado!\n", checkAt);
            }
            
            //(*gotSystemPauseIgnore) = true;
        }
        else{
            if(i == (checkLimit-1)){
                printf("\nTestar %lld:", checkAt);
            }

            if(op == 2){
                (*gotSystemPauseIgnore) = false;
            }

            if(markDownSwitch){
                if(i == (checkLimit-1)){
                    printf("\nEliminado!\n");
                }

                if(op == 3){
                    (*gotSystemPauseIgnore) = false;
                }

                temp->markDown = true;
                markDownCount++;

                markDownSwitch = false;
            }
            else{

                if(i == (checkLimit-1)){
                    printf("\nNao eliminado!\n");
                }

                //if(op == 3){
                //    (*gotSystemPauseIgnore) = true;
                //}

                markDownSwitch = true;
            }
        }

        if(temp->prox == NULL){
            //printf("\nReached end!");
            if(op == 4){
                (*gotSystemPauseIgnore) = false;
            }

            markIgnore(head);
            temp = head;
        }
        else{
            temp = temp->prox;
        }
    }

    //printf("\nTotal of %lld markdowns so far\n", markDownCount);
    return markDownCount;
}

void resetListStatuses(PESSOA *head){

    if(head == NULL){
        printf("\nErro na busca da cabeca da lista 'head' em resetListStatuses\n");
        system("pause");
        exit(-1);
    }

    PESSOA *temp = head;

    while(temp != NULL){
        temp->ignore = false;
        temp->markDown = false;

        temp = temp->prox;
    }

    //printf("\nCleared ignore values!\n");
}

long long calcularEleitoPorFormula(long long n){
    long long potencia = log2(n);
    long long m = n - pow(2, potencia);
    long long result = (2*m)+1;

    return result;
}

long long buscaEleito(PESSOA *head){

    if(head == NULL){
        printf("\nErro na busca da cabeca da lista 'head' em buscaEleito\n");
        system("pause");
        exit(-1);
    }

    PESSOA *temp = head;
    while(temp != NULL){
        if(!(temp->markDown)){
            return temp->num;
        }

        temp = temp->prox;
    }
}



int main(){

    printf("\nPrograma criado por Stormingness\n");
    printf("\n#################################\n");

    long long limit;

    printf("\n");

    do{
        printf("Insira o numero de pessoas: ");
        scanf("%lld", &limit);
    }while(limit < 1);

    if(limit == 1){
        printf("\n");

        printf("\n--> eleito(%lld) = %lld\n\n", limit, 1);

        system("pause");

        return -1;
    }

    int op;

    printf("\n--- MENU ---");
    printf("\n1. Tabela de valores");
    printf("\n2. Avaliacao por pessoa");
    printf("\n3. Avaliacao por eliminacao");
    printf("\n4. Avaliacao por ciclo");
    printf("\n5. Avaliacao completa");
    do{
        printf("\nInsira opcao do menu: ");
        scanf("\n%d", &op);
    }while(op < 1 || op > 5);

    printf("\n");

    long long i;

    if(op == 1){
        printf("\nPessoas\t\tEleito\n");

        for(i=0; i<limit; i++){
            printf("\n%lld\t\t%lld", i+1, calcularEleitoPorFormula(i+1));
        }

        printf("\n");

        printf("\n--> eleito(%lld) = %lld", limit, calcularEleitoPorFormula(limit));
        printf("\n\n");
        system("pause");
    }
    else{
        PESSOA *ListaPessoas = CriaPessoa(1);

        i=2;

        for(i=2; i<=limit; i++){
            ListaPessoas = AdicionaPessoa(ListaPessoas, CriaPessoa(i));
        }

        i=0;

        system("echo. > simulacao_eleito.txt");

        long long markDownCount = 0;
        bool ignoreSystemPause = false;

        while(markDownCount < (limit-1)){

            resetListStatuses(ListaPessoas);

            //printf("\nGoing to test mark down on %lld\n", i+1);

            markDownCount = changeMarkDown(ListaPessoas, i+1, &ignoreSystemPause, limit, op);
            outputFilePerTime(ListaPessoas, "simulacao_eleito.txt", limit);

            i++;

            if(ignoreSystemPause){
                ignoreSystemPause = false;
            }
            else{
                system("pause");
            }
        }

        printf("\n--> eleito(%lld) = %lld", limit, buscaEleito(ListaPessoas));
        printf("\n\n");
        system("pause");
    }

    return -1;
}
