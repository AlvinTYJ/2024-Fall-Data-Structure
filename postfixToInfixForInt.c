#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

struct Stack {
    int top;
    int items[MAX];
};

void initStack(struct Stack* s) {
    s->top = -1;
}

void push(struct Stack* s, int item) {
    if (s->top >= MAX - 1) {
        //printf("Stack overflow\n");
        exit(1);
    }
    s->items[++(s->top)] = item;
}

int pop(struct Stack* s) {
    if (s->top < 0) {
        //printf("Stack underflow\n");
        exit(1);
    }
    return s->items[(s->top)--];
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int applyOperator(int op1, int op2, char operator) {
    switch (operator) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': 
            if (op2 != 0)
                return op1 / op2;
            else {
                printf("Invalid\n");
                exit(1);
            }
        default: 
            printf("Invalid\n");
            exit(1);
    }
}

int postfixToInfix(char* postfix_exp) {
    struct Stack s;
    initStack(&s);

    char* token = strtok(postfix_exp, " ");
    int op1 = 0;
    int op2 = 0;
    int result = 0;

    while (token != NULL) {
        if (isOperator(token[0]) && strlen(token) == 1) {
            op2 = pop(&s);
            op1 = pop(&s);
            result = applyOperator(op1, op2, token[0]);
            push(&s, result);
        }
        else {
            int operand = atoi(token);
            push(&s, operand);
        }
        token = strtok(NULL, " ");
    }
    return pop(&s);
}

int main() {
    char postfix_exp[MAX];
    fgets(postfix_exp, MAX, stdin);
    postfix_exp[strcspn(postfix_exp, "\n")] = 0;

    int result = postfixToInfix(postfix_exp);
    printf("Result: %d\n", result);

    return 0;
}
