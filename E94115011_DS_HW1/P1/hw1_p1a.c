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

char* prefixToInfix(char* prefix_exp) {
    struct Stack s;
    initStack(&s);

    int length = strlen(prefix_exp);

    for (int i = length - 1; i >= 0; i--) {
        if (isOperator(prefix_exp[i])) {
            char* op1 = pop(&s);
            char* op2 = pop(&s);

            char* temp = (char*)malloc(strlen(op1) + strlen(op2) + 2);
            sprintf(temp, "%s%c%s", op1, prefix_exp[i], op2);
            push(&s, temp);
        }
        else {
            char* operand = (char*)malloc(2);
            operand[0] = prefix_exp[i];
            operand[1] = '\0';
            push(&s, operand);
        }
    }
    return pop(&s);
}

int main() {
    char prefix_exp[MAX];
    scanf("%s", prefix_exp);
    printf("%s\n", prefixToInfix(prefix_exp));
    return 0;
}