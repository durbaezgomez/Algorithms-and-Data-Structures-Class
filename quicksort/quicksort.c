#include<stdio.h>

int Partition(int A[], int p, int r);
void Quicksort(int A[], int p, int r);
void swapValues(int* a, int* b);
void ShowArray(int arr[],int n);

int main()
{

    int tab[] = {5,7,3,14,45,2,1,8};
    int n = sizeof(tab)/sizeof(tab[0]);

    printf("Tablica przed posortowaniem:\n");
    ShowArray(tab,n);
    printf("\n");

    Quicksort(tab, 0, n-1);
    printf("\nTablica po sortowaniu:\n");
    ShowArray(tab,n); 

    return 0;
}

int Partition(int A[],int p,int r){
    int x=A[r]; //element wyznaczajacy podział
    int i=(p-1); // indeks granicy
    for (int j=p; j<=(r-1); j++){
        if (A[j] <= x){
            i++;
            swapValues(&A[i], &A[j]);
        }      
    } 
    swapValues(&A[i+1],&A[r]);
    // printf("%d <-> %d\n",A[i+1],A[r]);
    return (i+1);
}
  
void Quicksort(int A[],int p,int r){
  if (p<r){
    int q = Partition(A, p, r);
    Quicksort(A, p, q-1);
    Quicksort(A, q + 1, r);
  }
}

void swapValues(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void ShowArray(int arr[], int n){
    for (int i = 0; i < n; i++){
        printf("%d ",arr[i]);
    }
}