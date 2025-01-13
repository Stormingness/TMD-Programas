#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CICLO_LIMITE 99999

int main(){
    printf("\nPrograma criado por Junior Coelho\n");
    printf("\n#################################\n");

    char a[80], b[80], c[80];

    FILE *f = fopen("congruencia.txt", "r");

    if(f == NULL){
        printf("\nErro na abertura do ficheiro.");
        return -1;
    }

    //fscanf(f, "%79[^^]^%79[^ ] = %d (mod %d)", a, b, &c, &d);

    fscanf(f, "%79[^^]^%79[^ ] mod %79[^;];\n", a, b, c);

    fclose(f);

    //printf("\n\nObitdo: %s, %s, %s", a, b, c);

    long long num1 = atol(a), num2 = atol(b), numMod = atol(c);

    //printf("\n%d, %d, mod = %d\n", num1, num2, numMod);

    printf("\nExpressao a calcular: %ld^%ld mod %ld\n", num1, num2, numMod);

    if((num1 % numMod) == 0){
        printf("\n%lld^%lld = %d^%lld = %d (mod %lld)\n", num1, num2, 0, num2, 0, numMod);
        printf("\nConclusao: Resto = 0");
    }
    else{
        if(num2 == 1){
            long long result = (num1 % numMod);
            printf("\n%lld^%lld = %lld = %lld (mod %lld)\n", num1, num2, num1, result, numMod);
            printf("\nConclusao: Resto = %lld", result);
        }

    else{
        int resto = num1 % numMod;
        printf("\n%lld^%lld = %lld^%lld (mod %ld)\n", num1, num2, resto, num2, numMod);

        int i, potencias[CICLO_LIMITE+1];

        potencias[0] = 1;
        potencias[1] = resto;

        printf("\nPotencias de %d:", resto);
        printf("\npotencias[0] = %d (mod %lld)", potencias[0], numMod);
        printf("\npotencias[1] = %d (mod %lld)\n", potencias[1], numMod);

        for(i=2; i<(CICLO_LIMITE+1); i++){

            int i_Q = (i/2);
            //printf("\ni = %d", i);

            int i_R;

            if((i % 2) == 0){
                i_R = i_Q;
            }
            else{
                i_R = i_Q;
                i_Q++;
            }
            //printf("\nQ(i/2) = %d", i_Q);
            //printf("\nR(i/2) = %d", i_R);

            //printf("\npotencias[i_Q] = %d\npotencias[i_R] = %d\n", potencias[i_Q], potencias[i_R]);

            int valor = potencias[i_Q]*potencias[i_R];
            potencias[i] = valor % numMod;
            printf("potencias[%d] = %d (mod %lld)\n", i, potencias[i], numMod);

            if(potencias[i] == potencias[1]){
                printf("\nCiclo de potencias termina em %d", i-1);
                //printf("\nTamanho do vetor = %d\n", i);
                break;
            }
        }
        i--;

        if(potencias[1] != potencias[i+1]){
            printf("\nErro no ciclo de potencias.");
            return -1;
        }

        //printf("i = %d", i);

        printf("\n\nLogo:");

        int j;

        for(j=1; j<i; j++){
            printf("\n%lld^(%dK+%d) = %d (mod %lld)", resto, i, j, potencias[j], numMod);
        }
        printf("\n%lld^(%dK) = %d (mod %lld)\n", resto, i, potencias[i], numMod);

        long long num2_Q = (num2 / i);
        int num2_R = (num2 % i);

        int resultResto_Q = (num2_R / 2);
        int resultResto_R;

        if((num2_R % 2) == 0){
                resultResto_R = resultResto_Q;
            }
            else{
                resultResto_R = resultResto_Q;
                resultResto_Q++;
            }
    
        int resultResto = potencias[resultResto_Q] * potencias[resultResto_R];
        int resultResto_Modded = resultResto % numMod;

        int result1 = potencias[i] * resultResto_Modded;

        if(result1 < numMod){

            if(resultResto == resultResto_Modded){

                printf("\n%lld^%lld = %lld^%lld = %lld^(%dx%lld + %d) = %lld^(%dx%lld) x %lld^%d = %d x %d = %d (mod %lld)\n", 
                    num1, num2, 
                    resto, num2, 
                    resto, i, num2_Q, num2_R,
                    resto, i, num2_Q, resto, num2_R,
                    potencias[i], resultResto,
                    result1,
                    numMod
                );

                printf("Conclusao: Resto = %d\n", result1);

            }
            else{

                printf("\n%lld^%lld = %lld^%lld = %lld^(%dx%lld + %d) = %lld^(%dx%lld) x %lld^%d = %d x %d = %d x %d = %d (mod %lld)\n", 
                    num1, num2, 
                    resto, num2, 
                    resto, i, num2_Q, num2_R,
                    resto, i, num2_Q, resto, num2_R,
                    potencias[i], resultResto,
                    potencias[i], resultResto_Modded,
                    result1,
                    numMod
                );

                printf("Conclusao: Resto = %d\n", result1);

            }
        }
        else{
        
            int result = result1 % numMod;

            printf("\n%lld^%lld = %lld^%lld = %lld^(%dx%ld + %d) = %d^(%dx%ld) x %d^%d = %d x %d = %d x %d = %d = %d (mod %ld)\n", 
                num1, num2, 
                resto, num2, 
                resto, i, num2_Q, num2_R,
                resto, i, num2_Q, resto, num2_R,
                potencias[i], resultResto,
                potencias[i], resultResto_Modded,
                result1,
                result,
                numMod
            );

            printf("Conclusao: Resto = %d\n", result);
        }
    }
    }

    printf("\n");

    system("pause");

    return -1;
}