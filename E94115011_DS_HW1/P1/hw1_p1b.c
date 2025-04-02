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

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

char* infixToPostfix(char* infix_exp) {
    struct Stack s;
    initStack(&s);
    
    char* postfix = (char*)malloc(MAX);
    int j = 0;

    int length = strlen(infix_exp);
    
    for (int i = 0; i < length; i++) {
        char current = infix_exp[i];
        
        if (isalnum(current)) {
            postfix[j++] = current;
        }
        else if (isOperator(current)) {
            while (s.top != -1 && precedence(s.items[s.top][0]) >= precedence(current)) {
                postfix[j++] = pop(&s)[0];
            }
            char* op = (char*)malloc(2);
            op[0] = current;
            op[1] = '\0';
            push(&s, op);
        }
    }

    while (s.top != -1) {
        postfix[j++] = pop(&s)[0];
    }

    postfix[j] = '\0';
    return postfix;
}

int main() {
    char infix_exp[MAX];
    scanf("%s", infix_exp);
    char* postfix = infixToPostfix(infix_exp);
    printf("%s\n", postfix);
    free(postfix);
    return 0;
}