#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MDN 254 // maks. dlugosc napisu
#define MN 10   // maks il napisow

char **inputList, **resultList, **tempList;
int wordLength[10], clear[10], lengthTMP[10];

int wordCount, maxLength;

void PrintArray(char **A);
void ReadWords();
void CountingSort();
void CheckLength();

int main()
{
    // a b c d e f g h i j k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26

    printf("Podaj ilosc wyrazow do wprowadzenia: (max 10)\n");
    scanf("%d", &wordCount);

    // ALOKUJE PAMIEC DLA TABLIC NA WYRAZY
    inputList = (char **)malloc(wordCount * sizeof(char *));
    resultList = (char **)malloc(wordCount * sizeof(char *));
    tempList = (char **)malloc(wordCount * sizeof(char *));

    ReadWords();

    printf("Wejsciowa tablica wyrazow:\n");
    PrintArray(inputList);
    
    CheckLength();

    CountingSort();

    printf("\nPosortowana tablica wyrazow:\n");
    PrintArray(resultList);
}

void ReadWords()  // wczytuje wyrazy do tablicy wejsciowej
{
    char word[MDN];
    for (int i = 0; i < wordCount; i++)
    {
        printf("Podaj wyraz: %d \n",i+1);
        scanf("%15s", word);
        inputList[i] = (char *)malloc(sizeof(char) * MDN);
        resultList[i] = (char *)malloc(sizeof(char) * MDN);
        tempList[i] = (char *)malloc(sizeof(char) * MDN);
        strcpy(inputList[i], word);
    }
    printf("\n");
}

void CheckLength()  // znajduje najdluzszy wyraz i zapisuje te wartosc do maxLength
{
    int tmp = 0;
    for (int i = 0; i < wordCount; i++)
    {
        if ((int)strlen(inputList[i]) > tmp)
            tmp = (int)strlen(inputList[i]);
        wordLength[i] = (int)strlen(inputList[i]);
    }
    maxLength = tmp;
}

int CharConverter(int letterNum, int letterIndex) // char -> ASCII
{
    if (wordLength[letterIndex] < letterNum)
        return 0;
    char character = *(inputList[letterIndex] + letterNum);

    if ((int)character >= 48 && (int)character <= 57)
        return (int)character - 47;
    if ((int)character >= 65 && (int)character <= 90)
        return (int)character - 64;
    if ((int)character >= 97 && (int)character <= 122)
        return (int)character - 96;
}

void CountingSort()
{
    printf("maxLength = %d\n", maxLength);
    int charCounter[27];

    for (int z = maxLength - 1; z >= 0; z--)
    {
        printf("Sortuje po bicie na miejscu %d\n\n", z+1);

        // najdalszy w sensie ASCII znak znaleziony w slowie
        int maxCharacter = CharConverter(z, 0); 

        for (int i = 1; i < wordCount; i++)
        {
            if (maxCharacter < CharConverter(z, i))
                maxCharacter = CharConverter(z, i);
        }

        // CountingSort

        // zeruje licznik znakow w wyrazach
        for (int i = 0; i <= maxCharacter; i++)
            charCounter[i] = 0;

        //zliczam wystepowanie znakow
        for (int i = 0; i < wordCount; i++)
            charCounter[CharConverter(z, i)]++;

        // sumuje liczniki kolejnych znakow 
        for (int i = 1; i <= maxCharacter; i++)
            charCounter[i] += charCounter[i - 1];

        for (int i = wordCount - 1; i >= 0; i--)
        {
            charCounter[CharConverter(z, i)] -= 1; // zmniejszam index znaku o 1
            strcpy(resultList[charCounter[CharConverter(z, i)]], inputList[i]); // kopiuje znak do tablicy wyjsciowej
            lengthTMP[charCounter[CharConverter(z, i)]] = wordLength[i]; // kopiuje wartosc dlugosci wyrazu
        }

        printf("AKTUALNY SORT:\n");
        PrintArray(inputList);

    }
}

void PrintArray(char **A)
{
    for (int i = 0; i < wordCount; i++)
    {
        printf("%s \n", A[i]);
    }
    printf("\n");
}
