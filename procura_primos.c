#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

//#define sizeOfVector 99999

typedef struct No{
    long long num;
    struct No *prox;
}NO;

NO *CriaNo(long long n){
    NO *novo = (NO*) malloc(sizeof(NO));
    novo->num = n;
    novo->prox = NULL;

    return novo;
}

NO *AdicionaNo(NO *head, NO *novo){
    if(head == NULL){
        printf("\nErro na busca da cabeca da lista 'head' em AdicionaNo\n");
    if(novo == NULL){
        printf("\nError na busca do elemdnto 'novo' da lista em AdicionaNo\n");
        return head;
    }

    NO *temp = head;

    while(temp->prox != NULL){
        temp = temp->prox;
    }
    temp->prox = novo;

    return head;
}



bool semLema(long long num);

bool comLema(long long num);

//long long getPrimes(long long *primeVector, int vectorSize, long long limit);
void getPrimes(NO *vetorPrimos, long long limit);

//bool comLemaTFA(long long num, long long *primeVector, long long vectorSize, int *numPrimes, long long *factVector);
bool comLemaTFA(long long num, NO *vetorPrimos, int *numPrimes, NO *factoresVectorPrimos);

//void factoriseNum(long long num, long long *primeVector, long long vectorSize);
void factorizarNum(long long num, NO *fatoresVetor);


int main(){

    printf("\nPrograma criada por Junior Coelho\n");
    printf("\n#################################\n");

/*
    int sec = time;

    int hour = sec / 3600;
    sec = sec - (hour*3600);

    int min = sec / 60;
    sec = sec - (min*60);
*/

    long long num;
    printf("\nInsira um numero: ");
    scanf("%lld", &num);
    //printf("\nGot: %lld\n", num);

    int op;

    printf("\n--- MENU ---");
    printf("\n1. Sem Lema");
    printf("\n2. Com Lema");
    printf("\n3. Com Lema + TFA\n");

    do{
    printf("Insira opcao do menu: ");
    scanf("%d", &op);
    }while(op < 1 || op > 3);

    clock_t startTime, endTime;
    double totalTime;
    bool isPrime;

    switch(op){
        case 1: startTime = clock();
                isPrime = semLema(num);
                endTime = clock();
                break;

        case 2: startTime = clock();
                isPrime = comLema(num);
                endTime = clock();
                break;

        case 3: //long long primes[sizeOfVector];
                NO *ListaPrimos = CriaNo(0);
                long long k;

                //long long newVectorSize = getPrimes(primes, sizeOfVector, num);
                //long long newVectorSize = getPrimes(ListaPrimos, num);
                getPrimes(ListaPrimos, num);

                int NumberOfPrimes;

                //long long factoriseVector[sizeOfVector];
                NO *fatoresVetorPrimos = CriaNo(0);

                startTime = clock();
                isPrime = comLemaTFA(num, ListaPrimos, &NumberOfPrimes, fatoresVetorPrimos);
                endTime = clock();

                //printf("\nNumber of factor primes: %d", NumberOfPrimes);

                if(NumberOfPrimes>0){
                    factorizarNum(num, fatoresVetorPrimos);
                }

                break;
        
        default: printf("\nErro na execucao da opcao %d", op);
    }

    totalTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;

    if(isPrime)
        printf("\n\n--> Conclusao: %lld e numero primo", num);
    else
        printf("\n\n--> Conclusao: %lld nao e numero primo", num);

    printf("\n\n--> Tempo total de execucao do metodo escolihdo (em segundos): %.9lf\n\n", totalTime);

    system("pause");
    return -1;
}

bool semLema(long long num){
    long long i;
    bool isPrime = true;

    for(i=2; i<num; i++){
        if((num % i) == 0){
            printf("\n%lld|%lld", i, num);
            isPrime = false;
            //break;
        }
    }

    return isPrime;
}

bool comLema(long long num){
    long long i;
    bool isPrime = true;

    for(i=2; i<=sqrt(num); i++){
        if((num % i) == 0){
            printf("\n%lld|%lld", i, num);
            isPrime = false;
            //break;
        }
    }

    return isPrime;
}

//long long getPrimes(NO *vetorPrimos, long long limit){
void getPrimes(NO *vetorPrimos, long long limit){

    long long i, j, pos=0, posCheck = 0;

    bool i_isPrime = true;

        for(i=2; i<=sqrt(limit); i++){
            for(j=2; j<=sqrt(i); j++){
                if((i % j) == 0){
                    //printf("\ni = %lld not prime", i);
                    i_isPrime = false;
                    break;
                }
            }

            if(i == 2){
                vetorPrimos->num = i;
            }
            else{
                if(i_isPrime){
                    //printf("\ni = %lld is prime", i);

                    NO *novoElemento = CriaNo(i);
                    vetorPrimos = AdicionaNo(vetorPrimos, novoElemento);

                    /*
                    NO *temp = vetorPrimos;

                    printf("\nPos before loop: %lld", pos);
                    printf("\nPosCheck before loop: %lld", posCheck);

                    for(posCheck = 0; posCheck < pos; posCheck++){
                        printf("\nPosCheck in loop: %lld", posCheck);
                        temp = temp->prox;
                        posCheck++;
                    }
                    printf("\nPosCheck after loop: %lld", posCheck);
                    //posCheck = 0;
                    */

                    //temp = novoElemento;

                    //printf("\nNumero neste temp = %lld\n", temp->num);

                    //primeVector[pos] = i;

                    //printf("\nprimeVector[%lld] = %lld", pos, primeVector[pos]);
                    //pos++;
                }
            }

            i_isPrime = true;
        }

        NO *temp1 = vetorPrimos;

        //printf("\n\nLISTA PRIMOS ATE RAIZ:");
        while(temp1 != NULL){
            //printf("\n%lld", temp1->num);
            temp1 = temp1->prox;
        }

    //return pos;
}

//bool comLemaTFA(long long num, long long *primesVector, long long vectorSize, int *numPrimes, long long *factVector){
bool comLemaTFA(long long num, NO *vetorPrimos, int *numPrimes, NO *fatoresVetorPrimos){ 
    long long i;
    bool isPrime = true;

    int NumOfPrimes = 0;

    NO *temp = vetorPrimos;

    //for(i=0; i<vectorSize; i++){
    while(temp != NULL){
        if((num % (temp->num)) == 0){
            printf("\n%lld|%lld", temp->num, num);
            isPrime = false;

            if(NumOfPrimes == 0){
                fatoresVetorPrimos->num = temp->num;
            }
            else{
                NO *novoElemento = CriaNo(temp->num);
                fatoresVetorPrimos = AdicionaNo(fatoresVetorPrimos, novoElemento);
            }
            NumOfPrimes++;
        }
        temp = temp->prox;
    }

    *numPrimes = NumOfPrimes;

    printf("\n\nTotal de divisores primos ate a raiz: %lld", NumOfPrimes);
    //printf("\nLISTA PRIMOS DIVISIVEIS ATE RAIZ:");
    NO *temp1 = fatoresVetorPrimos;
    while(temp1 != NULL){
        //printf("\n%lld", temp1->num);
        temp1 = temp1->prox;
    }

    return isPrime;
}

//void factoriseNum(long long num, long long *primeVector, long long vectorSize){
void factorizarNum(long long num, NO *fatoresVetor){
    
    printf("\n");

    long long number = num;

    //long long exponentVector[vectorSize];
    NO *exponentesVetor = CriaNo(0);

    NO *temp = fatoresVetor;

    while(temp->prox != NULL){
        NO *novoElemento = CriaNo(0);
        exponentesVetor = AdicionaNo(exponentesVetor, novoElemento);

        temp = temp->prox;
    }

    /*
    for(j=1; j<numFatores; j++){
        exponentVector[j] = 0;
    }
    */

    //int k;

    NO *temp1 = fatoresVetor;
    NO *temp2 = exponentesVetor;

    //for(k=0; k<vectorSize; k++){
    while(temp1 != NULL);
        while((number % (temp1->num)) == 0){
            number = number / (temp1->num);
            (temp2->num)++;
        }

        temp1 = temp1->prox;
        temp2 = temp2->prox;
    }

    printf("\nTeorema Fundamental da Aritmetica:\n%lld = ", num);

    //int n;

    temp1 = fatoresVetor;
    temp2 = exponentesVetor;

    //for(n=0; n<(vectorSize-1); n++){
    while(temp2->prox != NULL){
        if(temp2->num == 1){
            printf("%lld x ", temp1->num);
        }
        else{
            printf("%lld^%lld x ", temp1->num, temp2->num);
        }

        temp1 = temp1->prox;
        temp2 = temp2->prox;
    }

    if(number>1){
        if(temp2->num == 1){
            printf("%lld x %lld", temp1->num, number);

        }
        else{
            printf("%lld^%lld x %lld", temp1-1>num, temp2->num, number);
        }
    }
    else{
        if(temp2->num == 1){
            printf("%lld", temp1->num);
        }
        else{
            printf("%lld^%lld", temp1->num, temp2->num);
        }
    }
}
