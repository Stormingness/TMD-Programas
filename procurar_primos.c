#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>



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
    }
    
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



void apresentaExplicacao(){
    printf("\n\n ##### FUNCIONALIDADE DO PROGRAMA #####\n");
    printf("\nAo iniciar o programa, vai ser pedido ao utilizador para inserir um numero.");
    printf("\nO programa pede ao utilizador para inserir um novo numero se este for < 2.");
    printf("\nEste numero agora passa a ser chamado o 'numero a avaliar' para simplificar a explicacao.");
    printf("\nO numero a avaliar sera o numero desejado para verificar se ele e ou nao primo.");
    printf("\nApos inserir o numero a avaliar, um menu vai aparecer que contem as opcoes para cada algoritmo.");
    printf("\nDepois, o programa pede ao utilizador para inserir a opcao do menu apresentado.");
    printf("\nO programa pede ao utilizador para inserir uma nova opcao se esta nao for valida.");

    printf("\n\nSe o utilizador inserir o numero '0', vai aparecer a explicacao do programa.");

    printf("\n\nSe o utilizador inserir o numero '1', vai executar o algoritmo 'Sem Lema'.");
    printf("\nO tempo do CPU e registado aqui como tempo inicial.");
    printf("\nEste algoritmo comeca com um numero i = 2.");
    printf("\nO algoritmo verifica se existe resto da divisao entre o numero a avaliar e o numero i.");
    printf("\nSe houver resto da divisao, entao nao se conclui que o numero a avaliar e primo ainda.");
    printf("\nLogo que nao houver resto da divisao (ou seja resto = 0), entao conclui-se que o numero a avaliar e primo.");
    printf("\nApos cada verificacao, o numero i incrementa um valor (+1) ate ao numero a avaliar.");
    printf("\nO algoritmo verifica a divisao para cada incremento de i, fazendo as mesmas conclusoes.");
    printf("\nCada vez que i divide o numero a avaliar, ele e registado no programa.");
    printf("\nQuando o algoritmo se conclui, o tempo do CPU e registado denovo aqui como tempo final.");
    printf("\nO tempo final e calculado como o quociente entre a variacao do tempo do CPU e 'CLOCKS_PER_SEC'.");
    printf("\n'CLOCKS_PER_SEC' e um valor que indica quanto tempo de processamento do CPU existe num segundo.");
    
    printf("\n\nSe o utilizador inserir o numero '2', vai executar o algoritmo 'Com Lema'.");
    printf("\nO tempo do CPU e registado aqui como tempo inicial.");
    printf("\nEste algoritmo comeca com um numero i = 2.");
    printf("\nO algoritmo verifica se existe resto da divisao entre o numero a avaliar e o numero i.");
    printf("\nSe houver resto da divisao, entao nao se conclui que o numero a avaliar e primo ainda.");
    printf("\nLogo que nao houver resto da divisao (ou seja resto = 0), entao conclui-se que o numero a avaliar e primo.");
    printf("\nApos cada verificacao, o numero i incrementa um valor (+1) ate a raiz do numero a avaliar.");
    printf("\nO algoritmo verifica a divisao para cada incremento de i, fazendo as mesmas conclusoes.");
    printf("\nCada vez que i divide o numero a avaliar, ele e registado no programa.");
    printf("\nQuando o algoritmo se conclui, o tempo do CPU e registado denovo aqui como tempo final.");
    printf("\nO tempo final e calculado como o quociente entre a variacao do tempo do CPU e 'CLOCKS_PER_SEC'.");
    printf("\n'CLOCKS_PER_SEC' e um valor que indica quanto tempo de processamento do CPU existe num segundo.");
    
    printf("\n\nSe o utilizador inserir o numero '3', vai executar o algoritmo 'Com Lema + TFA'.");
    printf("\nO algoritmo inicia a calcular os numeros primos que divide o numero a avaliar ate a raiz do mesmo.");
    printf("\nEstes numeros sao guardados numa lista (ligada) para armazenar os numeros primos.");
    printf("\nEmbora irrelevante, o tempo do calculo dos numeros primos e igualmente medido como nos outros algoritmos.");
    printf("\nO tempo do CPU e registado aqui como tempo inicial (para o algoritmo pretendido).");
    printf("\nEste algoritmo comeca com um numero i = primeiro numero da lista de numeros primos.");
    printf("\nO algoritmo verifica se existe resto da divisao entre o numero a avaliar e o numero i.");
    printf("\nSe houver resto da divisao, entao nao se conclui que o numero a avaliar e primo ainda.");
    printf("\nLogo que nao houver resto da divisao (ou seja resto = 0), entao conclui-se que o numero a avaliar e primo.");
    printf("\nApos cada verificacao, o numero i muda para o seguinte numero na lista.");
    printf("\nO algoritmo verifica a divisao para cada mudanca de i, fazendo as mesmas conclusoes.");
    printf("\nCada vez que i divide o numero a avaliar, ele e registado no programa.");
    printf("\nQuando o algoritmo se conclui, o tempo do CPU e registado denovo aqui como tempo final.");
    printf("\nO tempo final e calculado como o quociente entre a variacao do tempo do CPU e 'CLOCKS_PER_SEC'.");
    printf("\n'CLOCKS_PER_SEC' e um valor que indica quanto tempo de processamento do CPU existe num segundo.");
    printf("\n--- BONUS ---");
    printf("\nApos o calculo do tempo final, o programa faz a decomposicao do numero a avaliar.");
    printf("\nEsta decomposicao mostra-se usando o Teorema Fundamental da Aritmetica.");
    printf("\nO programa divide o numero a avaliar por cada numero primo armazenado.");
    printf("\nPode haver varias divisoes do mesmo numero primo para calcular o seu expoente.\n\n");
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



void getPrimes(NO *vetorPrimos, long long limit){

    long long i, j, pos=0, posCheck = 0;

    bool i_isPrime = true;

    NO *temp = vetorPrimos;

    for(i=2; i<=sqrt(limit); i++){
        //for(j=2; j<=sqrt(i); j++){
        while(temp != NULL){
            if(temp->num != 0){
                if((i % (temp->num)) == 0){
                    //printf("\ni = %lld not prime", i);
                    i_isPrime = false;
                    break;
                }
            }
            temp = temp->prox;
        }

        if(i == 2){
            vetorPrimos->num = i;
        }
        else{
            if(i_isPrime){
                //printf("\ni = %lld e primo", i);

                NO *novoElemento = CriaNo(i);
                vetorPrimos = AdicionaNo(vetorPrimos, novoElemento);

            }
        }

        i_isPrime = true;
        temp = vetorPrimos;
    }

    NO *temp1 = vetorPrimos;

    //printf("\n\nLISTA PRIMOS ATE RAIZ:");
    while(temp1 != NULL){
        //printf("\n%lld", temp1->num);
        temp1 = temp1->prox;
    }
}

bool comLemaTFA(long long numAvaliar, NO *vetorPrimos, int *numPrimes, NO *fatoresVetorPrimos){ 
    long long i;
    bool isPrime = true;

    int NumOfPrimes = 0;

    NO *temp = vetorPrimos;

    //for(i=0; i<vectorSize; i++){
    while(temp != NULL){
        if((numAvaliar % (temp->num)) == 0){
            printf("\n%lld|%lld", temp->num, numAvaliar);
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

void factorizarNum(long long numAvaliar, NO *fatoresVetor){

    printf("\n");

    long long number = numAvaliar;

    NO *exponentesVetor = CriaNo(0);

    NO *temp = fatoresVetor;

    while(temp->prox != NULL){
        NO *novoElemento = CriaNo(0);
        exponentesVetor = AdicionaNo(exponentesVetor, novoElemento);

        temp = temp->prox;
    }

    NO *temp1 = fatoresVetor;
    NO *temp2 = exponentesVetor;

    while(temp1 != NULL){
        while((number % (temp1->num)) == 0){
            number = number / (temp1->num);
            (temp2->num)++;
        }

        temp1 = temp1->prox;
        temp2 = temp2->prox;
    }

    printf("\nTeorema Fundamental da Aritmetica:\n%lld = ", numAvaliar);

    temp1 = fatoresVetor;
    temp2 = exponentesVetor;

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
            printf("%lld^%lld x %lld", temp1->num, temp2->num, number);
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



int main(){

    printf("\nPrograma criada por Stormingness\n");
    printf("\n#################################\n");

    long long num;

    printf("\n");

    do{
    printf("Insira um numero: ");
    scanf("%lld", &num);
    }while(num < 2);

    int op;

    printf("\n--- MENU ---");
    printf("\n0. Funcionalidade do Programa");
    printf("\n1. Sem Lema");
    printf("\n2. Com Lema");
    printf("\n3. Com Lema + TFA\n");

    do{
    printf("Insira opcao do menu: ");
    scanf("%d", &op);
    }while(op < 0 || op > 3);

    clock_t startTime, endTime;
    double totalTime;
    bool isPrime;

    switch(op){
        case 0: apresentaExplicacao();
                break;

        case 1: printf("\nExecutar algoritmo...\n");
        
                startTime = clock();
                isPrime = semLema(num);
                endTime = clock();
                break;

        case 2: printf("\nExecutar algoritmo...\n");
        
                startTime = clock();
                isPrime = comLema(num);
                endTime = clock();
                break;

        case 3: NO *ListaPrimos = CriaNo(0);
                long long k;

                printf("\nCalcular os numeros primos ate a raiz...\n");

                startTime = clock();
                getPrimes(ListaPrimos, num);
                endTime = clock();

                int NumberOfPrimes;

                printf("\nCalculo dos numeros primos ate a raiz completo!\n");

                totalTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;

                printf("\n--> Tempo total do calculo dos numeros primos ate a raiz (em segundos): %.9lf\n\n", totalTime);

                NO *fatoresVetorPrimos = CriaNo(0);

                printf("\nExecutar algoritmo...\n");

                startTime = clock();
                isPrime = comLemaTFA(num, ListaPrimos, &NumberOfPrimes, fatoresVetorPrimos);
                endTime = clock();

                //printf("\nNumero de divisores que sao primos: %d", NumberOfPrimes);

                if(NumberOfPrimes>0){
                    factorizarNum(num, fatoresVetorPrimos);
                }

                break;
        
        default: printf("\nErro na execucao da opcao %d", op);
    }

    if(op == 0){
        system("pause");

        return -1;
    }
    else{
        totalTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;

        if(isPrime)
            printf("\n\n--> Conclusao: %lld e numero primo", num);
        else
            printf("\n\n--> Conclusao: %lld nao e numero primo", num);

        printf("\n\n--> Tempo total de execucao do metodo escolihdo (em segundos): %.9lf\n\n", totalTime);

        system("pause");

        return -1;
    }
}
