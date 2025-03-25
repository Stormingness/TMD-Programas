#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct List{
    int num;
    struct List *next;
}LIST;

LIST* newElement(int n){
    LIST *new = (LIST*) malloc(sizeof(LIST));
    new->num = n;
    new->next = NULL;
    return new;
}

LIST* addElement(LIST* head, LIST* new){
    if(head == NULL){
        printf("\nList head not found.");
        return new;
    }

    if(new == NULL){
        printf("\nInvalid new element.");
        return head;
    }

    LIST *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = new;

    //free(temp);

    return head;
}

void BubbleSortVector(int* vector, int size){
    bool isSorted = false;
    int i;

    while(!isSorted){
        isSorted = true;
        for(i=0; i<(size-2); i++){
            if(vector[i] > vector[i+1]){
                isSorted = false;

                int temp = vector[i+1];
                vector[i+1] = vector[i];
                vector[i] = temp;
            }
        }
    }
}

int main(){

    printf("\n### Program created by Stormingness ###\n");

    int p;

    printf("\nInsert a p: ");
    scanf("%d", &p);

    int a;

    LIST *generators = NULL;

    for(a=1; a<p; a++){
        int i, *potencias, *remainders;
        potencias = (int*) malloc((p-1)*sizeof(int));
        remainders = (int*) malloc((p-1)*sizeof(int));

        potencias[0] = a%p;
        remainders[0] = a%p;
        potencias[1] = (a*a)%p;
        remainders[1] = (a*a)%p;

        printf("\nPowers of %d:", a);
        printf("\n%d^%d = %d (mod %d)", a, 1, potencias[0], p);
        printf("\n%d^%d = %d (mod %d)\n", a, 2, potencias[1], p);

        for(i=2; i<(p-1); i++){

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

            int valor = potencias[i_Q-1]*potencias[i_R-1]*a;
            potencias[i] = valor % p;
            remainders[i] = valor % p;
            printf("%d^%d = %d (mod %d)\n", a, i+1, potencias[i], p);
        }

        BubbleSortVector(remainders, p-1);

        int j;
        bool isGenerator = true;

        for(j=0; j<(p-1); j++){
            if(remainders[j] == remainders[j+1]){
                isGenerator = false;
                break;
            }
        }

        //free(potencias);
        //free(remainders);

        if(isGenerator){
            printf("\n%d is generator of %d.\n\n", a, p);
            generators = addElement(generators, newElement(a));
        }
        else{
            printf("\n%d is not generator of %d.\n\n", a, p);
        }
    }

    LIST *temp1 = generators;

    if(temp1 == NULL){
        printf("\n--> %d has no generators.\n", p);
    }
    else{
        printf("\n--> Generators of %d: ", p);

        while(temp1->next != NULL){
            printf("%d, ", temp1->num);
            temp1 = temp1->next;
        }
        printf("%d.\n", temp1->num);
    }

    //free(temp1);

    printf("\n");
    system("pause");

    return -1;
}