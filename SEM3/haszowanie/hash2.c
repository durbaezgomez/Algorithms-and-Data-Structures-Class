#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element
{
    int numb;
    char val[30];
} hashElement;

int HashKey(long int, int, int);
float InsertRatioCount(hashElement *, int);
void PrintHashTable(hashElement *, int);

int HashKey(long int k, int i, int m)
{
    int hashedResult = ((k % m) + i * i) % m;
    return hashedResult;
}

float InsertRatioCount(hashElement *T, int m)
{
    float amount;
    for (int i = 0; i < m; i++)
    {
        if (T[i].numb != 0)
            amount++;
    }
    return 1-(amount / m);
}

void PrintHashTable(hashElement *T, int m)
{

    for (int i = 0; i < m; i++)
    {
        printf("%d. number: %d \nKey: %s\n\n", i + 1, T[i].numb, T[i].val);
    }
}

void DeleteFromHashTable(hashElement *T, int m)
{
    int counter = 0;
    int i;
    do
    {
        if (T[i].numb != 0)
        {

            T[i].numb = -1;
            for (int j = 0; j < 30; j++)
            {
                T[i].val[j] = 0;
            }
            counter++;
        }

    } while (counter > 0.4 * m);
}

int CountDeleted(hashElement *T, int m)
{
    int del = 0;
    for (int i = 0; i < m; i++)
    {
        if (T[i].numb == -1)
            del++;
    }
    return del;
}

int main()
{

    int testNumbers[] = { 10, 12, 14, 13, 17, 11 }; 

    for (int i = 0; i < 1; i++)
    {
        hashElement *T;

        int m = testNumbers[i];
        int licz = 0;
        int counter = 0;        
        
        T = (hashElement *)calloc(m, sizeof(hashElement));
        FILE *file = fopen("nazwiskaASCII.txt", "r");

        if (file == NULL)
        {
            printf("FILE COULDNT BE OPENED");
            return 1;
        }

        int number;
        char key[30];

        for (int j = 0; j < 30; j++)
            key[j] = 0;

        long int hashedResult;

        while (fscanf(file, "%d %s", &number, key) == 1 && InsertRatioCount(T, m) <= 0.5)
        {

            int blad = 0;
            counter = 2;

            hashedResult = (int)key[0] * 10 + (int)key[1];
            do
            {
                hashedResult = hashedResult * 10 + (int)key[counter];

                if (hashedResult < 0)
                {
                    blad = 1;
                    break;
                }

                counter++;
            } while (key[counter] != 0);

            if (blad != 1)
            {
                int skok = 0;
                while (1)
                {
                    if (T[HashKey(hashedResult, skok, m)].numb == 0)
                    {

                        T[HashKey(hashedResult, skok, m)].numb = number;
                        strcpy(T[HashKey(hashedResult, skok, m)].val, key);
                    }
                    else
                        skok++;
                }
            }
            licz++;

            for (int j = 0; j < 30; j++)
                key[j] = 0;
        }
        // zeruje  klucze
        for (int j = 0; j < 30; j++)
            key[j] = 0;

        PrintHashTable(T, m);
        DeleteFromHashTable(T, m);
        // PrintHashTable(T, m);
        CountDeleted(T, m);

        ////////////////////////

        fclose(file);

        // PrintHashTable(T, m);
        CountDeleted(T, m);

        free(T);
    }

    return 0;
}