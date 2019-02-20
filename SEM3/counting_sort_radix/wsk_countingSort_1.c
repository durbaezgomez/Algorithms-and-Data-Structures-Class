// wskazowka do sortowania pozycyjnego
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MDN 254 // maks. dlugosc napisu
#define MN 10   // maks il napisow

char *A[MN], *B[MN], *T[MN];

void drukuj(char *A[], int n)
{
    // drukuje  drugie litery napisow i napisy
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%c %s", *(A[i] + 1), A[i]);
        //czyli   printf("%c %s",*(*(A+i)+1),*(A+i));
        printf("\n");
    }
}

void czytaj(char *A[], int ilosc)
{
    char slowo[MDN];
    int i = 0;
    for (i = 0; i < ilosc; i++)
    {
        scanf("%s", slowo);
        A[i] = (char *)malloc(sizeof(char) * MDN);
        strcpy(A[i], slowo);
    }
}

main()
{
    int n = 2;
    printf("tablica A: \n");
    czytaj(A, n);
    printf("tablica A: \n");
    drukuj(A, n);
}