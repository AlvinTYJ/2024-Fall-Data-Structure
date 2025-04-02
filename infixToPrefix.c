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

// Reverse string helper function
void reverse(char* exp) {
    int len = strlen(exp);
    for (int i = 0; i < len / 2; i++) {
        char temp = exp[i];
        exp[i] = exp[len - i - 1];
        exp[len - i - 1] = temp;
    }
}

// Modification: Convert infix to prefix
char* infixToPrefix(char* infix_exp) {
    struct Stack s;
    initStack(&s);

    // Modification: Reverse the infix expression for prefix conversion
    reverse(infix_exp);
    
    // Modification: Swap parentheses in reversed expression
    for (int i = 0; i < strlen(infix_exp); i++) {
        if (infix_exp[i] == '(')
            infix_exp[i] = ')';
        else if (infix_exp[i] == ')')
            infix_exp[i] = '(';
    }

    char* prefix = (char*)malloc(MAX);
    int j = 0;

    int length = strlen(infix_exp);
    
    for (int i = 0; i < length; i++) {
        char current = infix_exp[i];
        
        if (isalnum(current)) {
            prefix[j++] = current;
        }
        else if (isOperator(current)) {
            while (s.top != -1 && precedence(s.items[s.top][0]) > precedence(current)) {
                prefix[j++] = pop(&s)[0];
            }
            char* op = (char*)malloc(2);
            op[0] = current;
            op[1] = '\0';
            push(&s, op);
        }
    }

    while (s.top != -1) {
        prefix[j++] = pop(&s)[0];
    }

    prefix[j] = '\0';

    // Modification: Reverse the result to get the correct prefix expression
    reverse(prefix);
    
    return prefix;
}

int main() {
    char infix_exp[MAX];
    scanf("%s", infix_exp);

    // Modification: Call infixToPrefix instead of infixToPostfix
    char* prefix = infixToPrefix(infix_exp);
    
    printf("%s\n", prefix);
    free(prefix);
    return 0;
}
