//
// Created by Aviv on 13/01/2022.
//

#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

typedef struct StackChar StackChar;
typedef struct StackInt StackInt;

struct StackChar {
    char value;
    struct StackChar *next;
    int (*isStackCharEmpty)();
    void (*pushStackChar)(char);
    char (*popStackChar)();
};

struct StackInt {
    int value;
    struct StackInt *next;
    void (*pushStackInt)(int);
    int (*popStackInt)();
};

StackChar *allocateStackChar();

StackInt *allocateStackInt();

StackChar *initStackChar(char val);

StackInt *initStackInt(int val);

int isStackCharEmpty(StackChar* root);

int isStackIntEmpty(StackInt* root);

char popStackChar(StackChar** node);

int popStackInt(StackInt** node);

StackChar *newStackChar();

StackInt *newStackInt();

void pushStackChar(StackChar** node, char val);

void pushStackInt(StackInt** node, int val);

#endif //PARSER_UTILS_H
