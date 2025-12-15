#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode
{
    char data[50];
    struct TreeNode *left;
    struct TreeNode *right;
};

#define STACK_SIZE 100
struct TreeNode *stack[STACK_SIZE];
int top = -1;

int isStackEmpty()
{
    return top == -1;
}

void push(struct TreeNode *node)
{
    if (top == STACK_SIZE - 1)
    {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = node;
}

struct TreeNode *pop()
{
    if (top == -1)
    {
        printf("Stack is empty\n");
        return NULL;
    }
    return stack[top--];
}

void create_r(struct TreeNode *root)
{
    char c;
    char d[50];
    printf("Do you want to add a left child to %s? (y/n): ", root->data);
    scanf(" %c", &c);
    if (c == 'y')
    {
        struct TreeNode *curr = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        printf("Data for new left node: ");
        scanf(" %s", d);
        strcpy(curr->data, d);
        curr->left = NULL;
        curr->right = NULL;
        root->left = curr;
        create_r(curr);
    }
    printf("Do you want to add a right child to %s? (y/n): ", root->data);
    scanf(" %c", &c);
    if (c == 'y')
    {
        struct TreeNode *curr = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        printf("Data for new right node: ");
        scanf(" %s", d);
        strcpy(curr->data, d);
        curr->left = NULL;
        curr->right = NULL;
        root->right = curr;
        create_r(curr);
    }
}

void create_nr(struct TreeNode *root)
{
    char ch = 'j';
    struct TreeNode *temp = root;
    do
    {

        int flag = 0;
        struct TreeNode *curr = (struct TreeNode *)malloc(sizeof(struct TreeNode));

        printf("Data for new node: ");
        scanf(" %s", curr->data);

        curr->left = NULL;
        curr->right = NULL;

        while (flag == 0)
        {
            char n;
            printf("Which node do you want to create for %s (l/r)? ", temp->data);
            scanf(" %c", &n);

            if (n == 'l')
            {
                if (temp->left == NULL)
                {
                    temp->left = curr;
                    flag = 1;
                }
                temp = temp->left;
            }
            else if (n == 'r')
            {
                if (temp->right == NULL)
                {
                    temp->right = curr;
                    flag = 1;
                }
                temp = temp->right;
            }
        }

        printf("Do you want to continue creating nodes? (y/n)\n");
        scanf(" %c", &ch);

    } while (ch == 'y');
}

void inorder_r(struct TreeNode *root)
{
    if (root != NULL)
    {
        inorder_r(root->left);
        printf("%s ", root->data);
        inorder_r(root->right);
    }
}

void inorder_nr(struct TreeNode *root)
{
    struct TreeNode *temp = root;
    while (1)
    {
        while (temp != NULL)
        {
            push(temp);
            temp = temp->left;
        }
        if (isStackEmpty())
        {
            break;
        }
        temp = pop();
        printf("%s ", temp->data);
        temp = temp->right;
    }
}

void preorder_r(struct TreeNode *root)
{
    if (root != NULL)
    {
        printf("%s ", root->data);
        preorder_r(root->left);
        preorder_r(root->right);
    }
}

void preorder_nr(struct TreeNode *root)
{
    struct TreeNode *temp = root;
    while (1)
    {
        while (temp != NULL)
        {
            printf("%s ", temp->data);
            push(temp);
            temp = temp->left;
        }
        if (isStackEmpty())
        {
            break;
        }
        temp = pop();
        temp = temp->right;
    }
}

void postorder_r(struct TreeNode *root)
{
    if (root != NULL)
    {
        postorder_r(root->left);
        postorder_r(root->right);
        printf("%s ", root->data);
    }
}

void postorder_nr(struct TreeNode *root)
{
    struct TreeNode *temp = root;
    while (1)
    {
        while (temp != NULL)
        {
            push(temp);
            temp = temp->left;
        }
        if (stack[top]->right == NULL)
        {
            temp = pop();
            printf("%s ", temp->data);
        }
        while (!isStackEmpty() && stack[top]->right == temp)
        {
            temp = pop();
            printf("%s ", temp->data);
        }
        if (isStackEmpty())
        {
            break;
        }
        temp = stack[top]->right;
    }
}

int main()
{
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    int c = 1;
    char d[50];

    printf("Data for root: ");
    scanf(" %s", d);
    strcpy(root->data, d);
    root->left = NULL;
    root->right = NULL;

    while (c != 0)
    {
        printf("1 for create 2 for create_nr 3 for inorder 4 for preorder 5 for postorder 6 for inorder_nr 7 for preorder_nr 8 for postorder_nr 0 for exit\n");
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            create_r(root);
            break;
        case 2:
            create_nr(root);
            break;
        case 3:
            printf("Inorder: ");
            inorder_r(root);
            printf("\n");
            break;
        case 4:
            printf("Preorder: ");
            preorder_r(root);
            printf("\n");
            break;
        case 5:
            printf("Postorder: ");
            postorder_r(root);
            printf("\n");
            break;
        case 6:
            printf("Inorder (non-recursive): ");
            inorder_nr(root);
            printf("\n");
            break;
        case 7:
            printf("Preorder (non-recursive): ");
            preorder_nr(root);
            printf("\n");
            break;
        case 8:
            printf("Postorder (non-recursive): ");
            postorder_nr(root);
            printf("\n");
            break;
        default:
            printf("Exiting....\n");
            break;
        }
    }
    return 0;
}