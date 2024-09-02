#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
    int size;
    int top;
    char *arr;
};

int isEmpty(struct stack *ptr) {
    return ptr->top == -1;
}

int isFull(struct stack *ptr) {
    return ptr->top == ptr->size - 1;
}

void push(struct stack* ptr, char val) {
    if (isFull(ptr)) {
        printf("Stack Overflow! Cannot push %c to the stack\n", val);
    } else {
        ptr->top++;
        ptr->arr[ptr->top] = val;
    }
}

char pop(struct stack* ptr) {
    if (isEmpty(ptr)) {
        printf("Stack Underflow! Cannot pop from the stack\n");
        return -1;
    } else {
        char val = ptr->arr[ptr->top];
        ptr->top--;
        return val;
    }
}

int stack_Top(struct stack* ptr) {
    return ptr->arr[ptr->top];
}

int precedence(char ch) {
    if (ch == '*' || ch == '/') {
        return 2;
    } else if (ch == '+' || ch == '-') {
        return 1;
    } else {
        return 0;
    }
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

char* infixtopostfix(char* infix) {
    struct stack* sp = (struct stack*) malloc(sizeof(struct stack));
    sp->size = 100;
    sp->top = -1;
    sp->arr = (char *)malloc(sp->size * sizeof(char));
    
    char* postfix = (char *)malloc((strlen(infix) + 1) * sizeof(char));
    int i = 0; // tracks infix traversal   
    int j = 0; // tracks postfix addition 
    
    while (infix[i] != '\0') {
        if (infix[i] >= 'a' && infix[i] <= 'z') {
            postfix[j++] = infix[i++];
        } else if (infix[i] == '(') {
            push(sp, infix[i++]);
        } else if (infix[i] == ')') {
            while (!isEmpty(sp) && stack_Top(sp) != '(') {
                postfix[j++] = pop(sp);
            }
            pop(sp);
            i++;
        } else {
            while (!isEmpty(sp) && precedence(infix[i]) <= precedence(stack_Top(sp))) {
                postfix[j++] = pop(sp);
            }
            push(sp, infix[i++]);
        } 
    }
    
    while (!isEmpty(sp)) {
        postfix[j++] = pop(sp);
    }
    
    postfix[j] = '\0';
    return postfix;       
}
int main() {
    char* infix = "a-(b+c)*d/(e+f)";
    printf("Postfix expression is: %s\n", infixtopostfix(infix));
    return 0;
}
