#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef unsigned long ul; 

typedef struct element
{
    int key;
    char value[30];
} hashElement;

int h(hashElement elem, int, int  m);
int HashInsert(hashElement *tableT, hashElement elem, int m, int *errorCount);
int InsertRatioCount(hashElement *, int m, float ratio);
void InitTable(hashElement *T, int m);
void PrintHashTable(hashElement *T, int m);
unsigned long WordToNum(hashElement elem, int m);

int h(hashElement elem, int i, int m)
{
    unsigned long k = WordToNum(elem, m);
    int hashedResult = ((k % m) + 2*i + 3*i^2) % m;
    // int hashedResult = ((k % m));
    return hashedResult;
}

unsigned long WordToNum(hashElement elem, int m)
{
    unsigned long wordLength = strlen(elem.value);
    // printf("%s, %lu\n",elem.value,wordLength);
    unsigned long k = 7 * elem.value[0] + elem.value[1];
    for (unsigned long i = 2; i < wordLength-1; i += 2)
    {
        k = (7 * elem.value[i] + elem.value[i + 1]) ^ k;   
    }
    // printf("\n%s: %d\n",elem.value, k);
    return k;   
}

int HashInsert(hashElement *tableT, hashElement elem, int m, int *errorCount)
{
    int i = 0;
    do
    {
        int j = h(elem, i, m);
        if (tableT[j].key == 0)
        {
            tableT[j] = elem;
            return j;
        }
        *errorCount=*errorCount+1;
        i++;
        // printf("CURRENT i = %d\n", i);

    } while (i < m);

}

void InitTable(hashElement *T, int m)
{
    for(int i = 0; i < m; i++){
        T[i].key=0;
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 30; j++)
            T[i].value[j] = 0;
    }
}

int InsertRatioCount(hashElement *T, int m, float ratio)
{
    int i;
    int counter = 0;
    for (i = 0; i < m; i++)
    {
        if (T[i].key != 0)
        {
            counter++;
        }
    }
    float isFilled = (float)counter / (float)m;
    if (isFilled >= ratio)
    {
        // printf("\nCURRENT  RATIO: %f\n",isFilled);
        return 1;
    }
    return 0;
}

void PrintHashTable(hashElement *T, int m)
{
    for (int i = 0; i < m; i++)
    {
        printf("%d. key: %d \nvalue: %s\n\n", i + 1, T[i].key, T[i].value);
    }
}

int main()
{
    // 1103, 1097, 1117, 1024, 1296, 1332
    // int testkeys[] = {1103, 1097, 1117, 1024, 1296, 1132§};
    int testkeys[] = {1200, 1300, 1400, 1201, 3169, 4451};
    // int testkeys[] = {2000, 3000, 4000, 227, 317, 447};

    float ratio[] = {0.5f, 0.7f,  0.9f};
    int index = 0;   // index po ktorym wstawiam klucze do tablicy
    int errorCount = 0;

    // zmienne potrzebne do wczytywania z pliku
    int key;
    char *buffer;

    for(int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 6; i++)
        {
            float testedRatio = ratio[j];
            int m = testkeys[i];
            int* wsk = &errorCount;

            index = 0;
            hashElement *T;
            T = (hashElement *)calloc(m, sizeof(hashElement));
            InitTable(T,m);

            FILE *file = fopen("nazwiskaASCII.txt", "r");
            if (file == NULL)
            {
                printf("FILE COULDNT BE OPENED");
            }

            do
            {
                if (fscanf(file, "%d %s", &key, &buffer) == 1)
                {
                    break;
                }
                hashElement elem;
                elem.key = key;
                strcpy(elem.value, &buffer);
                // WordToNum(elem,m);
                index = HashInsert(T, elem, m, wsk);
                // printf("%d, %s\n", elem.key,&elem.value);
            }while(!InsertRatioCount(T,m,testedRatio));

            errorCount = 0;
            for(int i = 0; i <= (m*5/100); i++)
            {
                    if (fscanf(file, "%d %s", &key, &buffer) == 1)
                    {
                        break;
                    }
                    hashElement elem;
                    elem.key = key;
                    strcpy(elem.value, &buffer);
                    int *wsk = &errorCount;
                    index = HashInsert(T, elem, m, wsk);
                    // printf("%d, %s\n", elem.key,&elem.value);
            }

            fclose(file);

            printf("\n\n%d. TRY: m = %d",i+1, m);
            printf("\nINSERT RATIO: %f",testedRatio);
            printf("\nERROR: %d\n",errorCount);
            float avg = errorCount/(float)m;
            printf("AVERAGE ERROR IN TRY:  %f", avg);
            free(T);
        }
    }
    

    return 0;
}