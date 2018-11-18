#include <stdio.h>
#include <stdlib.h>

void heapify(int[], int);
void swap(int[], int, int);
void buildHeap(int[], int);
void heapSort(int[], int);
void printArray(int[], int);
void writeToFile(int[], int);

int heapSize = 0;

int main()
{
    FILE *integers;
    integers = fopen("integers.txt", "r");

    int tempInt;
    int *array = NULL;
    size_t arraySize = 0;

    while (fscanf(integers, "%d", &tempInt) == 1)
    {
        int *tempArray = realloc(array, (arraySize + 1) * sizeof(int));
        if (tempArray != NULL)
        {
            array = tempArray;
            array[arraySize++] = tempInt;
        }
    }

    fclose(integers);

    heapSort(array, arraySize);

    printf("\nSorted array is: \n");
    printArray(array, arraySize);

    writeToFile(array, arraySize);
}

void heapify(int arrayToSort[], int index)
{
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int largest = index;

    if (leftChild <= heapSize && arrayToSort[leftChild] > arrayToSort[index])
    {
        largest = leftChild;
    }
    if (rightChild <= heapSize && arrayToSort[rightChild] > arrayToSort[largest])
    {
        largest = rightChild;
    }

    if (largest != index)
    {
        swap(arrayToSort, index, largest);
        heapify(arrayToSort, largest);
    }
}

void heapifyIteratively(int arrayToSort[], int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        swap(arrayToSort, 0, i);
        heapSize--;

        int j = 0, index;

        do
        {
            index = (2 * j + 1);

            if (arrayToSort[index] < arrayToSort[index + 1] && index < (i - 1))
                index++;

            if (arrayToSort[j] < arrayToSort[index] && index < i)
                swap(arrayToSort, j, index);

            j = index;

        } while (index < i);
    }
}

void swap(int arr[], int x, int y)
{
    int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
}

void buildHeap(int arr[], int size)
{
    heapSize = size - 1;
    for (int i = heapSize / 2 - 1; i >= 0; i--)
    {
        heapify(arr, i);
    }
}

void heapSort(int arr[], int size)
{
    buildHeap(arr, size);
    // for (int i = size - 1; i >= 0; i--)
    // {
    //     swap(arr, 0, i);
    //     heapSize--;
    //     //heapify(arr, 0);
    // }
    heapifyIteratively(arr, size);
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; ++i)
        printf("%d ", arr[i]);

    printf("\n");
}

void writeToFile(int arr[], int size)
{
    FILE *f = fopen("sorted.txt", "w");

    int i;
    for (i = 0; i < size; i++)
    {
        fprintf(f, "%d\n", arr[i]);
    }

    fclose(f);
}