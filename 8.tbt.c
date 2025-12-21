#include <stdio.h>
#include <stdlib.h>

struct tbtnode
{
    char data;
    int rbit, lbit;
    struct tbtnode *right;
    struct tbtnode *left;
};

void create(struct tbtnode *head)
{
    struct tbtnode *root = (struct tbtnode *)malloc(sizeof(struct tbtnode));
    printf("Enter Data for Root: ");
    scanf(" %c", &root->data);
    head->lbit = 1;
    head->left = root;
    root->lbit = root->rbit = 0;
    root->left = root->right = head;

    char c;
    do
    {
        struct tbtnode *curr = (struct tbtnode *)malloc(sizeof(struct tbtnode));
        printf("Enter Data for node to be added : ");
        scanf(" %c", &curr->data);

        curr->rbit = curr->lbit = 0;
        int flag = 0;
        struct tbtnode *temp = root;

        while (flag == 0)
        {
            char ch;
            printf("Enter %c at (l/r) of %c: ", curr->data, temp->data);
            scanf(" %c", &ch);

            if (ch == 'l')
            {
                if (temp->lbit == 0)
                {
                    curr->right = temp;
                    curr->left = temp->left;
                    temp->left = curr;
                    temp->lbit = 1;
                    flag = 1;
                }
                else
                {
                    temp = temp->left;
                }
            }
            else if (ch == 'r')
            {
                if (temp->rbit == 0)
                {
                    curr->left = temp;
                    curr->right = temp->right;
                    temp->right = curr;
                    temp->rbit = 1;
                    flag = 1;
                }
                else
                {
                    temp = temp->right;
                }
            }
            else
            {
                printf("Invalid choice! Please enter 'l' or 'r'.\n");
            }
        }

        printf("Do you want to continue adding nodes? (y/n): ");
        scanf(" %c", &c);
    } while (c == 'y');
}

struct tbtnode *inordersucc(struct tbtnode *temp)
{
    struct tbtnode *x = temp->right;

    if (temp->rbit == 1)
    {
        while (x->lbit == 1)
        {
            x = x->left;
        }
    }
    return x;
}

void inorder(struct tbtnode *head)
{
    struct tbtnode *temp = head->left;

    if (temp == head)
    {
        printf("Tree is empty!\n");
        return;
    }

    while (temp->lbit == 1)
    {
        temp = temp->left;
    }

    while (1)
    {
        printf("%c ", temp->data);
        temp = inordersucc(temp);
        if (temp == head)
        {
            break;
        }
    }
}

void preorder(struct tbtnode *head)
{
    struct tbtnode *temp = head->left;

    while (temp != head)
    {
        printf("%c ", temp->data);
        while (temp->lbit == 1)
        {
            temp = temp->left;
            printf("%c ", temp->data);
        }
        while (temp->rbit == 0 && temp->right != head)
        {
            temp = temp->right;
        }
        if (temp->rbit == 1)
        {
            temp = temp->right;
        }
        else
        {
            temp = head;
        }
    }
}

int main()
{
    struct tbtnode *head = (struct tbtnode *)malloc(sizeof(struct tbtnode));
    head->rbit = 1;
    head->lbit = 0;
    head->right = head;
    head->left = head;

    create(head);
    printf("Inorder: ");
    inorder(head);
    printf("\n");
    printf("Preorder: ");
    preorder(head);
    printf("\n");
    return 0;
}