#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MDN 254 // maks. dlugosc napisu
#define MN 10   // maks il napisow

char *inputList[MN], *resultList[MN];

void drukuj(char *A[], int n);

int main()
{
    // a b d e f g h i j k l  m  n  o  p  q  r  s  t  u  v  w  x  y  z 
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 


    inputList[0] = "wojsko";
    inputList[1] = "wujek";
    inputList[2] = "atom";

    int n = 2;

    drukuj(inputList,n);

    // CountingSort(inputList,resultList, 21);

    // printf(inputList);
    // printf("\n");
    // printf(resultList);
    


}

/*
Counting-sort(inputList resultList,k)
inputList - tablica do sortowania
resultList - wynik sortowania
k - zakres warości w tablicy inputList
charCounter - pomocnicza tablica "liczników"

for i=1 to k
charCounter[i]=0   
*/

void CountingSort(char* inputList[],char* resultList[], int k){

    char* charCounter;

    int length = sizeof(inputList) / sizeof(inputList[0]);

    for (int i = 0; i<k; i++)
    {
        charCounter[i] = 0;
    }

    // for j=1 to inputList.length
    // charCounter[inputList[j]] = charCounter[inputList[j]]+1;

    for (int j = 0; j < length; j++)
    {
        charCounter[*(inputList[j])] = charCounter[*(inputList[j])] + 1;
    }

    // teraz charCounter[i] == ilość wartości równych "i" w tablicy inputList
    // for i=2 to k
    // charCounter[i]=charCounter[i]+charCounter[i-1]

    for (int i = 2; i < k; i++)
    {
        charCounter[i] = charCounter[i] + charCounter[i - 1];
    }

    // teraz charCounter[i] == ilość wartości mniejszych lub równych "i" w inputList
    // for j=inputList.length downto 1
    // resultList[charCounter[inputList[j]]]=inputList[j]
    // charCounter[inputList[j]]=charCounter[inputList[j]]-1

    for (int j = length; j > 0; j--)
    {
        resultList[charCounter[*(inputList[j])]] = inputList[j];
        charCounter[*(inputList[j])] = charCounter[*(inputList[j])] - 1;
    }
}

void drukuj(char *A[], int n)
{
    // drukuje  pierwsze litery napisow i napisy
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%c %s", *(A[i]), A[i]);
        //czyli   printf("%c %s",*(*(A+i)+1),*(A+i));
        printf("\n");
    }
}
