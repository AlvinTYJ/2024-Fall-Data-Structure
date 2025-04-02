#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

struct Stack {
    int top;
    char* items[MAX];
};

void initStack(struct Stack* s) {
    s->top = -1;
}

void push(struct Stack* s, char* item) {
    if (s->top >= MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    s->items[++(s->top)] = strdup(item);
}

char* pop(struct Stack* s) {
    if (s->top < 0) {
        printf("Stack underflow\n");
        return NULL;
    }
    return s->items[(s->top)--];
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

char* postfixToInfix(char* postfix_exp) {
    struct Stack s;
    initStack(&s);

    int length = strlen(postfix_exp);

    for (int i = 0; i < length; i++) {
        if (isOperator(postfix_exp[i])) {
            char* op2 = pop(&s);
            char* op1 = pop(&s);
            char* temp = (char*)malloc(strlen(op1) + strlen(op2) + 2);
            sprintf(temp, "%s%c%s", op1, postfix_exp[i], op2);
            push(&s, temp);
        } else {
            char* operand = (char*)malloc(2);
            operand[0] = postfix_exp[i];
            operand[1] = '\0';
            push(&s, operand);
        }
    }
    return pop(&s);
}

int main() {
    char postfix_exp[MAX];
    scanf("%s", postfix_exp);
    printf("Infix expression: %s\n", postfixToInfix(postfix_exp));

    return 0;
}
