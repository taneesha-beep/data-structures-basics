#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char keyword[50];
    char meaning[100];
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(char *keyword, char *meaning)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->keyword, keyword);
    strcpy(newNode->meaning, meaning);
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *insert(Node *root, char *keyword, char *meaning)
{
    if (root == NULL)
    {
        return createNode(keyword, meaning);
    }
    if (strcmp(keyword, root->keyword) < 0)
    {
        root->left = insert(root->left, keyword, meaning);
    }
    else if (strcmp(keyword, root->keyword) > 0)
    {
        root->right = insert(root->right, keyword, meaning);
    }
    return root;
}

Node *minValueNode(Node *node)
{
    Node *current = node;
    while (current && current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

Node *deleteNode(Node *root, char *keyword)
{
    if (root == NULL)
    {
        return root;
    }
    if (strcmp(keyword, root->keyword) < 0)
    {
        root->left = deleteNode(root->left, keyword);
    }
    else if (strcmp(keyword, root->keyword) > 0)
    {
        root->right = deleteNode(root->right, keyword);
    }
    else
    {
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node *temp = minValueNode(root->right);
        strcpy(root->keyword, temp->keyword);
        strcpy(root->meaning, temp->meaning);
        root->right = deleteNode(root->right, temp->keyword);
    }
    return root;
}

void displayLevelWise(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    Node *queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front < rear)
    {
        Node *current = queue[++front];
        printf("%s: %s\n", current->keyword, current->meaning);
        if (current->left != NULL)
        {
            queue[++rear] = current->left;
        }
        if (current->right != NULL)
        {
            queue[++rear] = current->right;
        }
    }
}

Node *mirror(Node *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    Node *newRoot = createNode(root->keyword, root->meaning);
    newRoot->left = mirror(root->right);
    newRoot->right = mirror(root->left);
    return newRoot;
}

Node *copy(Node *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    Node *newRoot = createNode(root->keyword, root->meaning);
    newRoot->left = copy(root->left);
    newRoot->right = copy(root->right);
    return newRoot;
}

int main()
{
    Node *root = NULL;
    root = insert(root, "apple", "A fruit");
    root = insert(root, "banana", "Another fruit");
    root = insert(root, "cherry", "A small fruit");

    printf("Dictionary (Level-wise):\n");
    displayLevelWise(root);

    root = deleteNode(root, "banana");
    printf("\nAfter deleting 'banana':\n");
    displayLevelWise(root);

    Node *mirroredRoot = mirror(root);
    printf("\nMirror Image (Level-wise):\n");
    displayLevelWise(mirroredRoot);

    Node *copiedRoot = copy(root);
    printf("\nCopied Dictionary (Level-wise):\n");
    displayLevelWise(copiedRoot);

    return 0;
}