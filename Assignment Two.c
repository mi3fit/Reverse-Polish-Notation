//NEEMA MUTANU
//SCT221-0378/2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    int top;
    char items[MAX];
} Stack;

void push(Stack *s, char value) {
    if (s->top == (MAX - 1)) {
        printf("Stack Full\n");
    } else {
        s->items[++s->top] = value;
    }
}

char pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Empty\n");
        return -1;
    } else {
        return s->items[s->top--];
    }
}

int isOperator(char symbol) {
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '%';
}

int precedence(char symbol) {
    switch (symbol) {
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
        case '%':
            return 3;
        default:
            return 0;
    }
}

void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    s.top = -1;
    int i, j = 0;
    char symbol;
    for (i = 0; i < strlen(infix); i++) {
        symbol = infix[i];
        if (isalnum(symbol)) {
            postfix[j++] = symbol;
        } else if (symbol == '(') {
            push(&s, symbol);
        } else if (symbol == ')') {
            while (s.items[s.top] != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s); // Remove '(' from stack
        } else if (isOperator(symbol)) {
            while (s.top != -1 && precedence(s.items[s.top]) >= precedence(symbol)) {
                postfix[j++] = pop(&s);
            }
            push(&s, symbol);
        }
    }
    while (s.top != -1) {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression: ");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = 0; // Remove newline character

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}
