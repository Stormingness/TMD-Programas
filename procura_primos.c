#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define sizeOfVector 99999

typedef struct No{
    long long n;
    long long *prox;
}NO;





bool semLema(long long num);
bool comLema(long long num);

long long getPrimes(long long *primeVector, int vectorSize, long long limit);

bool comLemaTFA(long long num, long long *primeVector, long long vectorSize, int *numPrimes, long long *factVector);

void factoriseNum(long long num, long long *primeVector, long long vectorSize);

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

    printf("\n\nAlgorithm Menu:");
    printf("\n1. Sem Lema");
    printf("\n2. Com Lema");
    printf("\n3. Com Lema + TFA\n");

    do{
    printf("Insert an option from the menu: ");
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

        case 3: long long primes[sizeOfVector];
                long long k;

                long long newVectorSize = getPrimes(primes, sizeOfVector, num);

                /*
                for(k=0; k<newVectorSize; k++){
                    printf("\nprimes[%lld] = %lld", k, primes[k]);
                }
                */

                int NumberOfPrimes;

                long long factoriseVector[sizeOfVector];

                startTime = clock();
                isPrime = comLemaTFA(num, primes, newVectorSize, &NumberOfPrimes, factoriseVector);
                endTime = clock();

                printf("\nNumber of factor primes: %d", NumberOfPrimes);

                if(NumberOfPrimes>0){
                    factoriseNum(num, factoriseVector, NumberOfPrimes);
                }
                break;
        
        default: printf("\nErro na execucao da opcao %d", op);
    }

    totalTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;

    if(isPrime)
        printf("\n\n%lld is prime? = true", num);
    else
        printf("\n\n%lld is prime? = false", num);

    printf("\nTotal function execution time in seconds: %.9lf\n", totalTime);

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

long long getPrimes(long long *primeVector, int vectorSize, long long limit){

    long long i, j, pos=0;

    bool i_isPrime = true;

        for(i=2; i<=sqrt(limit); i++){
            for(j=2; j<=sqrt(i); j++){
                if((i % j) == 0){
                    //printf("\ni = %lld not prime", i);
                    i_isPrime = false;
                    break;
                }
            }

            if(i_isPrime){
                printf("\ni = %lld is prime", i);
                primeVector[pos] = i;
                printf("\nprimeVector[%lld] = %lld", pos, primeVector[pos]);
                pos++;
            }

            i_isPrime = true;
        }

    return pos;
}

bool comLemaTFA(long long num, long long *primesVector, long long vectorSize, int *numPrimes, long long *factVector){
    long long i;
    bool isPrime = true;

    int NumOfPrimes = 0;

    for(i=0; i<vectorSize; i++){
        if((num % primesVector[i]) == 0){
            printf("\n%lld|%lld", primesVector[i], num);
            isPrime = false;
            factVector[NumOfPrimes] = primesVector[i];
            NumOfPrimes++;
            //break;
        }
    }

    *numPrimes = NumOfPrimes;

    return isPrime;
}

void factoriseNum(long long num, long long *primeVector, long long vectorSize){
    
    long long number = num;

    long long exponentVector[vectorSize];
    int j;

    for(j=0; j<vectorSize; j++){
        exponentVector[j] = 0;
    }

    int k;

    for(k=0; k<vectorSize; k++){
        while((number % primeVector[k]) == 0){
            number = number / primeVector[k];
            exponentVector[k]++;
        }
    }

    printf("\n%lld = ", num);

    int n;

    for(n=0; n<vectorSize-1; n++){
        if(exponentVector[n] == 1){
            printf("%lld x ", primeVector[n]);
        }
        else{
            printf("%lld^%lld x ", primeVector[n], exponentVector[n]);
        }
    }

    if(number>0){
        if(exponentVector[vectorSize-1] == 1){
            printf("%lld x %lld\n", primeVector[vectorSize-1], number);

        }
        else{
            printf("%lld^%lld x %lld\n", primeVector[vectorSize-1], exponentVector[vectorSize-1], number);
        }
    }
    else{
        if(exponentVector[vectorSize-1] == 1){
            printf("%lld\n", primeVector[vectorSize-1]);
        }
        else{
            printf("%lld^%lld\n", primeVector[vectorSize-1], exponentVector[vectorSize-1]);
        }
    }
}