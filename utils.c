//
// Created by Aviv on 13/01/2022.
//

#include <malloc.h>
#include "utils.h"

StackChar *allocateStackChar() {
    return (struct StackChar *) malloc(sizeof(struct StackChar));
}

StackInt *allocateStackInt() {
    return (struct StackInt *) malloc(sizeof(struct StackInt));
}

StackChar *initStackChar(char val) {
    StackChar *n = allocateStackChar();
    n->value = val;
    n->next = NULL;
    return n;
}

StackInt *initStackInt(int val) {
    StackInt *n = allocateStackInt();
    n->value = val;
    n->next = NULL;
    return n;
}

int isStackCharEmpty(StackChar* root) {
    return root == NULL;
}

int isStackIntEmpty(StackInt* root) {
    return root == NULL;
}

char popStackChar(StackChar** node) {
    struct StackChar* tmp = *node;
    char val = tmp->value;
    *node = (*node)->next;
    free(tmp);
    return val;
}

int popStackInt(StackInt** node) {
    struct StackInt* tmp = *node;
    int val = tmp->value;
    *node = (*node)->next;
    free(tmp);
    return val;
}

StackChar *newStackChar() {
    StackChar *n = allocateStackChar();
    n->next = NULL;
    return n;
}

StackInt *newStackInt() {
    StackInt *n = allocateStackInt();
    n->next = NULL;
    return n;
}

void pushStackChar(StackChar** node, char val) {
    struct StackChar* temp = initStackChar(val);
    temp->next = *node;
    *node = temp;
}

void pushStackInt(StackInt** node, int val) {
    struct StackInt* temp = initStackInt(val);
    temp->next = *node;
    *node = temp;
}


