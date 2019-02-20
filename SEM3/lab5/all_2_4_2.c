#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void Heapify(int arr[], int n, int i);
void BuildHeap(int arr[], int n);

int main()
{

    FILE *fp;
    fp = fopen("integers.txt", "r");

    int temp;
    int *liczby = NULL;
    size_t n = 0;

    //WCZYTYWANIE Z PLIKU
    while (fscanf(fp, "%d", &temp) == 1)
    {
        int *tempArray = realloc(liczby, (n+1) * sizeof(int));
        if (tempArray != NULL)
        {
            liczby = tempArray;
            liczby[n++] = temp;
            printf("%d \n",temp);
        }
    }

    fclose(fp);

    printf("przed sortowaniem: \n");
    for (int i = 0; i < n; i++)
    {
        printf("%i ", liczby[i]);
    }

    BuildHeap(liczby,n);

    //ZAPISYWANIE DO PLIKU
    FILE *fp2;
    fp2 = fopen("sorted.txt", "w");

    for (int i = 0; i < n; i++)
    {
        fprintf(fp2, "%d\n", liczby[i]);
    }

    fclose(fp2);

    printf("\npo sortowaniu: \n");
    for (int i = 0; i < n; i++)
    {
        printf("%i ", liczby[i]);
    }
}

void Heapify(int arr[],int n ,int i){

    int largest = i;
    int l = 2 * i+1;          //lewy syn
    int r = 2 * i+2;      // prawy syn

    if (l <= n-1 && arr[l] > arr[largest]){
        largest = l;
    }
    if (r < n-1 && arr[r] > arr[largest])
    {
        largest = r;
    }
    if (largest != i){
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        Heapify(arr, n, largest);
    }
}

void BuildHeap(int arr[], int n){

    // printf("\n\n%d", n);

    for (int i = n/2-1; i>=0; i--)
        Heapify(arr, n, i);
        
            
    for (int i = n-1; i>=0; i--){
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        Heapify(arr, i, 0);
    }
}
