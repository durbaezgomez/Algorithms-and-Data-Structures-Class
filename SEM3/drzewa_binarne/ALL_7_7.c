#include <stdio.h>
#include <stdlib.h>

struct node
{
    int day;
    int month;
    int value;
    struct node *left, *right;
};

struct node *CreateNewNode(int item, int item2, int item3)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->day = item;
    temp->month = item2;
    temp->value = item3;
    temp->left = temp->right = NULL;
    return temp;
}

void PrintTreeInOrder(struct node *root)
{
    if (root != NULL)
    {
        PrintTreeInOrder(root->left);
        printf("%d ", root->value);
        PrintTreeInOrder(root->right);
    }
}

struct node *InsertNewNode(struct node *node, int tempDay, int tempMonth, int tempValue)
{

    if (node == NULL)
        return CreateNewNode(tempDay, tempMonth, tempValue);

    int nodeDate = node->month * 100 + node->day;
    int insertDate = tempMonth * 100 + tempDay;

    // printf("\nVALUE: %d, TEMPDATE: %d", tempValue, nodeDate);

    if (insertDate < nodeDate)
        node->left = InsertNewNode(node->left, tempDay, tempMonth, tempValue);

    if (insertDate > nodeDate)
        node->right = InsertNewNode(node->right, tempDay, tempMonth, tempValue);

    return node;
}

struct node *FindSmallestNode(struct node *node)
{
    struct node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

struct node *DeleteNode(struct node *node, int sDay, int sMonth)
{
    if (node == NULL)
        return node;

    int nodeDate = node->month * 100 + node->day;
    int deleteDate = sMonth * 100 + sDay;

    if (deleteDate < nodeDate)
        node->left = DeleteNode(node->left, sDay, sMonth);

    else if (deleteDate > nodeDate)
        node->right = DeleteNode(node->right, sDay, sMonth);

    else
    {
        if (node->left == NULL)
        {
            struct node *temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            struct node *temp = node->left;
            free(node);
            return temp;
        }

        struct node *temp = FindSmallestNode(node->right);

        node->day = temp->day;
        node->month = temp->month;
        node->value = temp->value;

        node->right = DeleteNode(node->right, temp->day, temp->month);
    }
    return node;
}

struct node *FindAlgorithm(struct node *node, int sDay, int sMonth)
{
    printf("\nSearching for node with date %d/%d...", sDay, sMonth);

    while(node != NULL){
        int nodeDate = node->month * 100 + node->day;
        int insertDate = sMonth * 100 + sDay;

        if (insertDate < nodeDate)
            node = node->left;
        else if (insertDate > nodeDate)
            node = node->right;
        else 
            return node;

    }
    return NULL;
}

void FindNodeByDate(struct node *node, int sDay, int sMonth)
{
    struct node *isFound = FindAlgorithm(node, sDay, sMonth);
    if(isFound != NULL)
        printf("\nThe value on the date %d/%d is %d.\n", isFound->day, isFound->month, isFound->value);
    else{
        int expectedValue = (FindAlgorithm(node, sDay - 1, sMonth)->value + FindAlgorithm(node, sDay + 1, sMonth)->value)/2;
            printf("\nNO NODE, EXPECTED value on that date %d/%d is %d.\n", sDay, sMonth, expectedValue);
    }
        
}

void MergeTrees(struct node *node1, struct node *node2)
{
    if (node1 != NULL && node2 != NULL)
    {
        MergeTrees(node1, node2->left);
        InsertNewNode(node1, node2->day, node2->month, node2->value);
        MergeTrees(node1, node2->right);
    }
}

void FindValuesBetweenDates(struct node * root, int day1, int month1, int day2, int month2)
{
    int leftBorder = month1 * 100 + day1;
    int rightBorder = month2 * 100 + day2;
    int tempDate = 0;
    if (root != NULL)
    {
        tempDate = root->month * 100 + root->day;

        if(tempDate >= leftBorder && tempDate <= rightBorder)
        {
            printf("%d ", root->value);
            FindValuesBetweenDates(root->left, day1, month1, day2, month2);
            FindValuesBetweenDates(root->right, day1, month1, day2, month2);
        }

        else if(tempDate > rightBorder)
            FindValuesBetweenDates(root->left, day1, month1, day2, month2);
        else if(tempDate < leftBorder)
            FindValuesBetweenDates(root->right, day1, month1, day2, month2);
    }
}


    int main()
{

    struct node *root = NULL;
    root = InsertNewNode(root, 1, 8, 220);
    InsertNewNode(root, 3, 2, 315);
    InsertNewNode(root, 20, 1, 230);
    InsertNewNode(root, 15, 4, 330);
    InsertNewNode(root, 17, 4, 310);
    InsertNewNode(root, 5, 3, 118);
    InsertNewNode(root, 3, 9, 155);

    printf("\nTREE:   ");
    PrintTreeInOrder(root); // PRINTING THE TREE IN ORDER

    // struct node *root2 = NULL;
    // root2 = InsertNewNode(root2, 7, 3, 121);
    // InsertNewNode(root2, 3, 11, 314);
    // InsertNewNode(root2, 20, 6, 139);
    // InsertNewNode(root2, 15, 8, 179);

    //MERGING TREES
    // printf("\n SECOND TREE:\n");
    // PrintTreeInOrder(root2); // PRINTING THE TREE IN ORDER
    // MergeTrees(root, root2); 
    // printf("\n AFTER MERGING\n");
    // PrintTreeInOrder(root); // PRINTING THE TREE IN ORDER

    // SEARCHING FOR NODES
    printf("\n");
    // FindNodeByDate(root, 16,4);
    FindValuesBetweenDates(root, 4, 2, 1, 8);

    // DELETING A NODE
    // DeleteNode(root, 15,4);
    // printf("\n");
    // PrintTreeInOrder(root);

    return 0;
}