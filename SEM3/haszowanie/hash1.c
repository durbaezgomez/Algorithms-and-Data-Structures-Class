#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CountZeros(int *T, int m)
{
    int zerosCounter = 0;
    for (int i = 0; i < m; i++)
    {
        if (T[i] == 0)
            zerosCounter++;
    }

    printf("\nNumber of zeros: %d", zerosCounter);
}

void CountMaxValue(int *T, int m)
{
    int max = T[0];
    for (int i = 1; i < m; i++)
    {
        if (T[i] > max)
            max = T[i];
    }

    printf("\nBiggest value: %d", max);
}

void CountAverageValue(int *T, int m)
{
    long int sum = 0;
    int nonZerosCounter = 0;
    for (int i = 0; i < m; i++)
    {
        if (T[i] != 0)
        {
            sum += T[i];
            nonZerosCounter++;
        }
    }
    sum /= nonZerosCounter;

    printf("\nAverage value: %ld\n", sum);
}

int main()
{
    int testNumbers[] = {
        1103,
        1097,
        1117,
        1331,
        1024,
        1296,
    };

    for (int i = 0; i < 6; i++)
    {
        int m;
        int count = 0;

        m = testNumbers[i];

        int nonZerosCounter = 0;
        int *T = (int *)malloc(sizeof(int) * m); // Tworze tablice T rozmiaru m T[m]

        for (int n = 0; n < m; n++)
            T[n] = 0;                           // zeruje tablice

        FILE *file = fopen("3700.txt", "r");    // otwieram plik

        if (file == NULL)                       // jesli plik nie zostal otwarty
        {
            printf("FILE COULDNT BE OPENED");
            return 1;
        }

        char key[30];                         

        for (int j = 0; j < 30; j++)
            key[j] = 0;                        // zmienna na kazdy klucz

        long long int result;

        while (fscanf(file, "%s", key) == 1 && count < 2 * m)
        {
            // printf("\nkey = %s\n", key);
            int errorFlag= 0;
            nonZerosCounter = 2;
            result = (int)key[0] * 7 + (int)key[1];
            do
            {
                result = result * 7 + (int)key[nonZerosCounter];

                if (result < 0)
                {
                    break;
                    errorFlag= 1;
                }

                nonZerosCounter++;
            } while (key[nonZerosCounter] != 0);

            if (errorFlag!= 1)
                T[result % m]++;

            count++;
            //printf("\nresult = %lli\n", result);

            for (int j = 0; j < 30; j++)
                key[j] = 0;
        }

        fclose(file);

        if (i < 3)
            printf("\nTEST %d. \nWartosc niekorzystna \n------------\nm = %d", i + 1, m);
        else
            printf("\nTEST %d. \nWartosc korzystna (liczby pierwsze) \n------------\nm = %d", i+1, m);

        CountZeros(T, m);
        CountMaxValue(T, m);
        CountAverageValue(T, m);

        free(T);            // zwalniam pamiec  po tablicy T
    }

    return 0;
}