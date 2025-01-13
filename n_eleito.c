#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//#define MAX 25

typedef struct Pessoa{
    long long num;
    int markDown;
    bool ignore;

    struct Pessoa *prox;
} PESSOA;


PESSOA *CriaPessoa(long long n){

    PESSOA *novo = (PESSOA*) malloc(sizeof(PESSOA));
    novo->prox = NULL;
    novo->markDown = 0;
    novo->ignore = false;
    novo->num = n;

    return novo;
}

PESSOA *AdicionaPessoa(PESSOA *head, PESSOA *novo){
    if(head == NULL){
        printf("\nError. head doesn't exist.");
        return novo;
    }

    if(novo == NULL){
        printf("\nError. novo doesn't exist.");
        return head;
    }

    PESSOA *temp = head;

    while(temp->prox != NULL){
        temp = temp->prox;
    }

    temp->prox = novo;

    //free(temp);

    return head;
}

void outputFilePerTime(PESSOA *head, char *fileName, long long limit){
    FILE *f = fopen(fileName, "w");

    if(f == NULL){
        printf("\nErro na abertura do ficheiro %s - line 54\n", fileName);
        system("pause");
    }

    PESSOA *temp = head;

    while(temp != NULL){
        //printf("\nNumero: %lld", ListaPessoas->num);
        fprintf(f, "%lld ", temp->num);
        temp = temp->prox;
    }

    fprintf(f, "\n");
    temp = head;

    while(temp != NULL){
        long long espacos = (long long) log10(temp->num);
        //printf("\nNumero de digitos: %lld", espacos);
        long long k;

        if(temp->markDown){
            fprintf(f, "X ");
        }
        else{
            fprintf(f, "O ");
        }

        for(k=0; k<espacos; k++){
            fprintf(f, " ");
        }

        temp = temp->prox;
    }

    /*
    if(temp == NULL){
        temp = head;
    }

    long long i;

    for(i=0; i<limit; i++){

        printf("\nThe limit I received was %lld\n", limit);
        printf("\nMarkdown is at %d", *markDownNum);

        if(*markDownNum){
            printf("\nI'm going to mark down %lld", i+1);
            temp->markDown = 1;
        }

        *markDownNum = (*markDownNum + 1) % 2;
        printf("\n\nMarkdown changed to %d\n", *markDownNum);

        temp = temp->prox;
    }
    */
    fclose(f);
}

void changeMarkDown(PESSOA *head, long long checkLimit, bool *gotIgnore, long long limit){
    PESSOA *temp = head;

    long long markDownNum = 0;

    long long i=0;
    printf("\nThe limit for checking is %lld", checkLimit);

    for(i=0; i<checkLimit; i++){

        (*gotIgnore) = false;

        long long checkAt = (i % limit) + 1;

        if(!(temp->ignore)){

            printf("\nTesting %lld", checkAt);
            if(markDownNum){
                printf("\nMarked down!\n");

                temp->markDown = 1;
                markDownNum = 0;

                //*markDownCount = *markDownCount + 1;
            }
            else{
                printf("\nNot marked down!\n");
                markDownNum = 1;
            }

            if(temp->prox == NULL){
                printf("\nReached end of list!\n");
                PESSOA *temp2 = head;

                while(temp2 != NULL){

                    if(temp2->markDown){
                        printf("\nIgnoring %lld\n", temp2->num);
                        temp2->ignore = true;
                    }
                    
                    temp2 = temp2->prox;
                }

                temp = head;
            }
            else{
                temp = temp->prox;
            }

        }
        else{
            printf("\nIgnored %lld\n", checkAt);

            (*gotIgnore) = true;

            if(temp->prox == NULL){
                temp = head;
            }
            else{
                temp = temp->prox;
            }
        }
    }
}


void resetListStatuses(PESSOA *head, long long limit){
    PESSOA *temp = head;

    while(temp != NULL){
        temp->ignore = false;
        temp->markDown = 0;

        temp = temp->prox;
    }

    printf("\nCleared ignore values!\n");
}

long long countTotalMarkDowns(PESSOA *head){
    long long markDownCount = 0;

    PESSOA *temp = head;
    while(temp != NULL){
        if(temp->markDown == 1){
            markDownCount++;
        }

        temp = temp->prox;
    }

    return markDownCount;
}

long long buscaEleito(PESSOA *head){
    PESSOA *temp = head;
    while(temp != NULL){
        if((temp->markDown) == 0){
            return temp->num;
        }
    }
}

int main(){

    printf("\nPrograma criado por Junior Coelho\n");
    printf("\n#################################\n");

    long long limit;

    printf("\nInsira um limite: ");
    scanf("%lld", &limit);

    if(limit == 1){
        printf("\n");

        printf("\neleito(%lld) = %lld\n\n", limit, 1);

        system("pause");

        return -1;
    }

    PESSOA *ListaPessoas = CriaPessoa(1);

    long long i=2;
    for(i=2; i<=limit; i++){
        ListaPessoas = AdicionaPessoa(ListaPessoas, CriaPessoa(i));
    }

    i=0;

    system("echo. > simulacao_eleito.txt");

    long long markDownCount = 0;
    bool getIgnore = false;

    while(markDownCount < (limit-1)){

        resetListStatuses(ListaPessoas, limit);

        printf("\nGoing to test mark down on %lld\n", i+1);

        changeMarkDown(ListaPessoas, i+1, &getIgnore, limit);
        outputFilePerTime(ListaPessoas, "simulacao_eleito.txt", i+1);

        markDownCount = countTotalMarkDowns(ListaPessoas);

        i++;

        printf("\nWe have %lld markdowns so far\n", markDownCount);

        if(getIgnore == true){
            getIgnore = false;
        }
        else{
            system("pause");
        }
    }

    printf("\nHi");

    printf("\neleito(%lld) = %lld\n\n", limit, buscaEleito(ListaPessoas));

    system("pause");

    return -1;
}