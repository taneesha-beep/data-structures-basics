#include <stdio.h>
#define MAX 100
typedef struct
{
    int row;
    int col;
    int value;
} Element;
typedef struct
{
    int rows;
    int cols;
    int num;
    Element elements[MAX];
} SparseMatrix;
void inputSparseMatrix(SparseMatrix *s)
{
    printf("enter no. of rows and columns: ");
    scanf("%d %d", &s->rows, &s->cols);
    printf("enter no. of non zero elements: ");
    scanf("%d", &s->num);
    printf("enter row, column and value of non zero elements:\n");
    for (int i = 0; i < s->num; i++)
    {
        scanf("%d %d %d", &s->elements[i].row, &s->elements[i].col, &s->elements[i].value);
    }
}
void printSparseMatrix(SparseMatrix s)
{
    printf("row\tcolumn\tvalue\n");
    for (int i = 0; i < s.num; i++)
    {
        printf("%d\t%d\t%d\n", s.elements[i].row, s.elements[i].col, s.elements[i].value);
    }
}
void fastTranspose(SparseMatrix s, SparseMatrix *t)
{
    int rowTerms[MAX] = {0}, startingPos[MAX];
    t->rows = s.cols;
    t->cols = s.rows;
    t->num = s.num;
    for (int i = 0; i < s.num; i++)
    {
        rowTerms[s.elements[i].col]++;
    }
    startingPos[0] = 0;
    for (int i = 1; i < s.cols; i++)
    {
        startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
    }
    for (int i = 0; i < s.num; i++)
    {
        int j = startingPos[s.elements[i].col]++;
        t->elements[j].row = s.elements[i].col;
        t->elements[j].col = s.elements[i].row;
        t->elements[j].value = s.elements[i].value;
    }
}
int main()
{
    SparseMatrix s, t;
    inputSparseMatrix(&s);
    printf("original sparse matrix:\n");
    printSparseMatrix(s);
    fastTranspose(s, &t);
    printf("fast transposed sparse matrix:\n");
    printSparseMatrix(t);
    return 0;
}