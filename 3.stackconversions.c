#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 100
#define MAX 100

int top = -1;
char stack[SIZE];

int isfull()
{
    return top == SIZE - 1;
}

int isempty()
{
    return top == -1;
}

void push(char e)
{
    if (isfull())
    {
        printf("Stack overflow\n");
    }
    else
    {
        stack[++top] = e;
    }
}

char pop()
{
    if (isempty())
    {
        printf("Stack empty\n");
        return '\0';
    }
    else
    {
        return stack[top--];
    }
}

char peek()
{
    if (isempty())
    {
        return '\0';
    }
    else
    {
        return stack[top];
    }
}

int icp(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    case '(':
        return 5;
    default:
        return 0;
    }
}

int isp(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 4;
    default:
        return 0;
    }
}

void infixToPostfix(char infix[], char postfix[])
{
    int i = 0, k = 0;
    char tkn = infix[i];

    while (tkn != '\0')
    {
        if (isalnum(tkn))
        {
            postfix[k++] = tkn;
        }
        else
        {
            if (tkn == '(')
            {
                push(tkn);
            }
            else if (tkn == ')')
            {
                while (!isempty() && peek() != '(')
                {
                    postfix[k++] = pop();
                }
                pop();
            }
            else
            {
                while (!isempty() && isp(peek()) >= icp(tkn))
                {
                    postfix[k++] = pop();
                }
                push(tkn);
            }
        }
        i++;
        tkn = infix[i];
    }

    while (!isempty())
    {
        postfix[k++] = pop();
    }
    postfix[k] = '\0';
}

int s_top = -1;
char s_stack[MAX][20];

int isStackFull()
{
    return s_top == MAX - 1;
}

int isStackEmpty()
{
    return s_top == -1;
}

void s_push(char str[])
{
    if (!isStackFull())
    {
        strcpy(s_stack[++s_top], str);
    }
    else
    {
        printf("Stack is Full\n");
    }
}

void s_pop(char str[])
{
    if (!isStackEmpty())
    {
        strcpy(str, s_stack[s_top--]);
    }
    else
    {
        printf("Stack is Empty\n");
    }
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

void postToinfix(char postfix[], int size)
{
    char str1[20], str2[20], infix[40], temp[2];
    int i = 0;

    while (postfix[i] != '\0')
    {
        if (!isOperator(postfix[i]))
        {
            temp[0] = postfix[i];
            temp[1] = '\0';
            s_push(temp);
        }
        else
        {
            s_pop(str1);
            s_pop(str2);
            strcpy(infix, "(");
            strcat(infix, str2);
            strncat(infix, &postfix[i], 1);
            strcat(infix, str1);
            strcat(infix, ")");
            s_push(infix);
        }
        i++;
    }

    s_pop(infix);
    printf("The infix expression is: %s\n", infix);
}

void preToinfix(char prefix[], int size)
{
    char str1[20], str2[20], infix[40], temp[2];

    for (int i = size - 1; i >= 0; i--)
    {
        if (!isOperator(prefix[i]))
        {
            temp[0] = prefix[i];
            temp[1] = '\0';
            s_push(temp);
        }
        else
        {
            s_pop(str1);
            s_pop(str2);
            strcpy(infix, "(");
            strcat(infix, str1);
            strncat(infix, &prefix[i], 1);
            strcat(infix, str2);
            strcat(infix, ")");
            s_push(infix);
        }
    }

    s_pop(infix);
    printf("The infix expression is: %s\n", infix);
}

void prefixToPostfix(char *prefix, char *postfix)
{
    int i;
    char op1[MAX], op2[MAX], temp[MAX];

    int len = strlen(prefix);
    s_top = -1;

    for (i = len - 1; i >= 0; i--)
    {
        if (isalnum(prefix[i]))
        {
            temp[0] = prefix[i];
            temp[1] = '\0';
            s_push(temp);
        }
        else
        {
            s_pop(op1);
            s_pop(op2);
            strcpy(temp, op1);
            strcat(temp, op2);
            strncat(temp, &prefix[i], 1);
            s_push(temp);
        }
    }

    s_pop(postfix);
}

int main()
{
    char infix[SIZE], postfix[SIZE], prefix[SIZE];
    char choice;
    int size;

    printf("Choose an option:\n");
    printf("1. Convert Infix to Postfix\n");
    printf("2. Convert Postfix to Infix\n");
    printf("3. Convert Prefix to Infix\n");
    printf("4. Convert Prefix to Postfix\n");
    printf("Enter your choice (1/2/3/4): ");
    scanf(" %c", &choice);
    getchar();

    switch (choice)
    {
    case '1':
        printf("Enter infix expression: ");
        fgets(infix, SIZE, stdin);
        infix[strcspn(infix, "\n")] = '\0';
        infixToPostfix(infix, postfix);
        printf("Postfix expression: %s\n", postfix);
        break;
    case '2':
        printf("Enter postfix expression: ");
        fgets(postfix, SIZE, stdin);
        postfix[strcspn(postfix, "\n")] = '\0';
        size = strlen(postfix);
        postToinfix(postfix, size);
        break;
    case '3':
        printf("Enter prefix expression: ");
        fgets(prefix, SIZE, stdin);
        prefix[strcspn(prefix, "\n")] = '\0';
        size = strlen(prefix);
        preToinfix(prefix, size);
        break;
    case '4':
        printf("Enter prefix expression: ");
        fgets(prefix, SIZE, stdin);
        prefix[strcspn(prefix, "\n")] = '\0';
        size = strlen(prefix);
        prefixToPostfix(prefix, postfix);
        printf("Postfix expression: %s\n", postfix);
        break;
    default:
        printf("Invalid choice!\n");
        break;
    }

    return 0;
}
