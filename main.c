#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>


typedef struct Node Node;
struct Node {
    char value;
    struct Node *next;
};

Node *allocate() {
    return (struct Node *) malloc(sizeof(struct Node));
}

Node *initNode(char val) {
    Node *n = allocate();
    n->value = val;
    n->next = NULL;
    return n;
}

int isEmpty(Node* root) {
    return root == NULL;
}

Node *newNode() {
    Node *n = allocate();
    n->next = NULL;
    return n;
}

char pop(Node** node) {
    struct Node* tmp = *node;
    char val = tmp->value;
    *node = (*node)->next;
    free(tmp);
    return val;
}

void push(Node** node, char val) {
    struct Node* temp = initNode(val);
    temp->next = *node;
    *node = temp;
}

int calculate(char* equation, int len) {
    Node *operator = newNode();
    Node *output = newNode();
    int offset = 0;
    for (int i = 0; i < len - offset; i += 2) {
// check for parentheses before doing anything else
        switch (equation[i]) {
            case '(': {
                int start = i + 1;
                int end;
                while (equation[i] != ')') {
                    i++;
                }
                end = i - 1;
                char subEq[end - start + 1];
                int index = 0;
                for (int j = start; j <= end; j++) {
                    subEq[index] = equation[j];
                    index++;
                }
                push(&output, (char)((calculate(subEq, sizeof(subEq)))+ 48));
                break;
            }

            case '*': {
                if (equation[i+1] == '*') {
                    i += 3;
                    int val = pow(pop(&output) - '0', equation[i] - '0');
                    push(&output, (char)(val + '0'));
                } else {
                    i += 2;
                    int val = (pop(&output) - '0') * (equation[i] - '0');
                    push(&output, (char)(val + '0'));
                }
                break;
            }
            case '/': {
                i += 2;
                int val = (pop(&output) - '0') / (equation[i] - '0');
                push(&output, (char)(val + '0'));
                break;
            }
            case '+': {
                push(&operator, equation[i]);
                break;
            }
            case '-': {
                push(&operator, equation[i]);
                break;
            }
            default: {
                char val = equation[i];
                push(&output, val);
                break;
            }
        }
    }

    while (!isEmpty(operator)) {
        char op = pop(&operator);
        if (op == '+') {
            int val = pop(&output) + pop(&output) - '0';
            push(&output, (char)val);
        } else if (op == '-') {
            int val = pop(&output) - pop(&output) + '0';
            push(&output, (char)val);
        }
    }

    return pop(&output) - '0';
}

int main() {
    char* equation = "3 ** (2 + 1)";
    int len = strlen(equation);

    char *ptr = equation;
    printf("%d", calculate(equation, len));
}