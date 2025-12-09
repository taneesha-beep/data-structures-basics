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
void transposeSparseMatrix(SparseMatrix s, SparseMatrix *t)
{
    t->rows = s.cols;
    t->cols = s.rows;
    t->num = s.num;
    int k = 0;
    for (int i = 0; i < s.cols; i++)
    {
        for (int j = 0; j < s.num; j++)
        {
            if (s.elements[j].col == i)
            {
                t->elements[k].row = s.elements[j].col;
                t->elements[k].col = s.elements[j].row;
                t->elements[k].value = s.elements[j].value;
                k++;
            }
        }
    }
}
int main()
{
    SparseMatrix s, t;
    inputSparseMatrix(&s);
    printf("original sparse matrix:\n");
    printSparseMatrix(s);
    transposeSparseMatrix(s, &t);
    printf("transposed sparse matrix:\n");
    printSparseMatrix(t);
    return 0;
}
