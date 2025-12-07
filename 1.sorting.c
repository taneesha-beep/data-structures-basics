// problem statement: Write a C program to create a student database using an array of structures. Apply Sorting techniques(Bubble sort ,Insertion Sort, Selection Sort).
#include <stdio.h>
struct Student
{
    int PRN;
    char name[30];
    char div;
    int mob;
};
void display(struct Student s[], int n);
void bubblesort(struct Student s[], int n);
void selectionsort(struct Student s[], int n);
int main()
{
    struct Student s[20];
    int n;
    printf("enter number of students: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("enter PRN: ");
        scanf("%d", &s[i].PRN);
        printf("enter your name:  ");
        scanf("%s", s[i].name);
        printf("enter division: ");
        scanf("%c", &s[i].div);
        printf("enter phone number:  ");
        scanf("%d", &s[i].mob);
    }
    printf(" before sorting:\n");
    display(s, n);
    bubblesort(s, n);
    printf("after sorting through PRN using bubble sort:\n");
    display(s, n);
    selectionsort(s, n);
    printf("after sorting through PRN using selection sort:\n");
    display(s, n);
    return 0;
}
void display(struct Student s[], int n)
{
    for (int j = 0; j < n; j++)
    {
        printf("PRN : %d NAME : %s DIV: %d PHONE NO: %d\n", s[j].PRN, s[j].name, s[j].div, s[j].mob);
    }
}
void bubblesort(struct Student s[], int n)
{
    struct Student temp;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (s[j].PRN > s[j + 1].PRN)
            {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}
void selectionsort(struct Student s[], int n)
{
    int index;
    struct Student temp;
    for (int i = 0; i < n - 1; i++)
    {
        index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (s[j].PRN < s[index].PRN)
            {
                index = j;
            }
        }
        if (index != i)
        {
            temp = s[i];
            s[i] = s[index];
            s[index] = temp;
        }
    }
}