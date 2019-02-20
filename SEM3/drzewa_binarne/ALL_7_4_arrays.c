#include <stdio.h>
#include <stdlib.h>

void  InitTree(int* Tree, int size);
void NoMoreNodes();
int TreeInsert(int * Tree, int size, int keyToInsert);
int TreeSearch(int* Tree, int node, int searchedKey);
void TreeDelete(int *Tree, int size, int node);
void TreePrint(int* Tree, int size);

void InitTree(int* Tree, int size)
{
    for (int i = 0; i < size+1; i++)
    {
        Tree[i] = NULL;
    }
}

void NoMoreNodes(int key){
    printf("No more free  nodes to  insert the key %d!\n",key);
}

int TreeInsert(int* Tree, int size, int keyToInsert)
{
    int node = 1;
    int y = NULL; // y jest ojcem node

    if(Tree[1] == NULL){
        Tree[1] = keyToInsert;
    }

    else{
        while (Tree[node] != NULL)
        {
            y = node; 
            if (keyToInsert < Tree[node])
            {   
                if(2*node > size){
                    NoMoreNodes(keyToInsert);
                    return 1;
                }
                else
                {
                    node = 2*node;
                }
            }
            else
            {
                if (2*node+1 > size)
                {
                    NoMoreNodes(keyToInsert);
                    return 1;
                }
                else
                {
                    node = 2*node+1;
                }
            }
        }
        Tree[node] = keyToInsert;
    }
    return 1;
}

int TreeSearch(int Tree[], int node, int searchedKey) // szuka searchedKey w poddrzewie o korzeniu node
{
    while (Tree[node] != NULL && searchedKey != Tree[node])
    {
        if (searchedKey < Tree[node])
        {
            node = 2*node;
        }
        else
        {
            node = 2*node+1;
        }
    }
    return node; // zwraca NULL gdy nie ma klucza searchedKey
}

void TreeDelete(int* Tree,  int size, int node)
{
        // TODO USUWANIE WEZLA Z DRZEWA
}
 
void TreePrint(int Tree[], int size)
{
    for (int i = 1; i < size+1; i++)
    {
        printf("%d   ",Tree[i]);
    }
}

int main()
{
    int Tree[7];
    InitTree(Tree, 7);

    TreeInsert(Tree, 7, 12);
    TreeInsert(Tree, 7, 7);
    TreeInsert(Tree, 7, 15);
    TreeInsert(Tree, 7, 4);
    TreeInsert(Tree, 7, 8);
    TreeInsert(Tree, 7, 14);
    TreeInsert(Tree, 7, 25);

    TreePrint(Tree, 7);

    printf("\n14 znajduje  sie  w wezle: %d",TreeSearch(Tree,1,14));
}