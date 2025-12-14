#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    char name[50];
    int prn;
    struct student *next;
};

int count(struct student *head)
{
    struct student *temp = head->next;
    int c = 0;
    while (temp != NULL)
    {
        temp = temp->next;
        c++;
    }
    return c;
}

void create(struct student *head)
{
    struct student *temp = head;
    char ch;
    do
    {
        struct student *current = (struct student *)malloc(sizeof(struct student));
        printf("Enter PRN: ");
        scanf("%d", &current->prn);
        printf("Enter name: ");
        scanf(" %49[^\n]", current->name);
        current->next = NULL;
        temp->next = current;
        temp = temp->next;
        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y');
}

void insert(struct student *head)
{
    int i = 1, p;
    struct student *curr = head;
    struct student *nnode = (struct student *)malloc(sizeof(struct student));
    char ch;
    int k = count(head);
    do
    {
        printf("Enter PRN: ");
        scanf("%d", &nnode->prn);
        printf("Enter name: ");
        scanf(" %49[^\n]", nnode->name);
        printf("Enter Position: ");
        scanf("%d", &p);
        if (p > k + 1)
        {
            printf("Position out of range.\n");
        }
        else
        {
            while (curr != NULL && i < p)
            {
                i++;
                curr = curr->next;
            }
            nnode->next = curr->next;
            curr->next = nnode;
        }
        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y');
}

void delete(struct student *head)
{
    int ctr = 1, p;
    char ch;
    struct student *prev = head;
    struct student *curr = head->next;
    int k = count(head);
    do
    {
        printf("Enter Position: ");
        scanf("%d", &p);
        if (p > k)
        {
            printf("Position out of range.\n");
        }
        else
        {
            while (ctr < p && curr != NULL)
            {
                ctr++;
                prev = curr;
                curr = curr->next;
            }
            struct student *temp = curr;
            prev->next = curr->next;
            curr->next = NULL;
            free(temp);
        }
        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y');
}

void display(struct student *head)
{
    struct student *temp = head->next;
    while (temp != NULL)
    {
        printf("PRN: %d\n", temp->prn);
        printf("Name: %s\n", temp->name);
        temp = temp->next;
    }
    printf("\n");
}

void reverse(struct student **head)
{
    struct student *prev = NULL;
    struct student *current = *head;
    struct student *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void sort(struct student *head)
{
    if (head == NULL)
        return;
    struct student *i, *j;
    int tempPrn;
    char tempName[50];
    for (i = head->next; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->prn > j->prn)
            {
                tempPrn = i->prn;
                i->prn = j->prn;
                j->prn = tempPrn;
                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);
            }
        }
    }
}

struct student *merge(struct student *head1, struct student *head2)
{
    struct student dummy;
    struct student *tail = &dummy;
    dummy.next = NULL;

    while (head1 != NULL && head2 != NULL)
    {
        if (head1->prn <= head2->prn)
        {
            tail->next = head1;
            head1 = head1->next;
        }
        else
        {
            tail->next = head2;
            head2 = head2->next;
        }
        tail = tail->next;
    }
    tail->next = (head1 != NULL) ? head1 : head2;

    return dummy.next;
}

void freeList(struct student *head)
{
    struct student *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    struct student *head = (struct student *)malloc(sizeof(struct student));
    head->next = NULL;
    struct student *head2 = (struct student *)malloc(sizeof(struct student));
    head2->next = NULL;
    int q = 1;
    while (q != 0)
    {
        printf("1 for create 2 for insert 3 for display 4 for deletion 5 for reverse 6 for sort 7 for merge 0 for exit\n");
        scanf("%d", &q);
        switch (q)
        {
        case 1:
            create(head);
            break;
        case 2:
            insert(head);
            break;
        case 3:
            display(head);
            break;
        case 4:
            delete(head);
            break;
        case 5:
            reverse(&head);
            break;
        case 6:
            sort(head);
            break;
        case 7:
            printf("Creating second list for merging:\n");
            create(head2);
            head = merge(head, head2);
            printf("Merged list:\n");
            display(head);
            freeList(head2); // Free the second list
            break;
        default:
            printf("Exiting...\n");
        }
    }
    freeList(head);
    return 0;
}
