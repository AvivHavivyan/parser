#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

StackInt* stringToStack(char* equation, int len) {
    int num = 0;
    StackInt* output = newStackInt();
    popStackInt(&output);
    for (int i = 0; i < len; i++) {
        num = 0;
        if (isdigit(equation[i]) != 0) {
            while (equation[i] != ' ' && i < len) {
                num *= 10;
                num += equation[i] - '0';
                i++;
            }
            pushStackInt(&output, num);
        }
    }
    return output;
}

StackChar* stringToOp(char* equation, int len) {
    StackChar* op = newStackChar();
    popStackChar(&op);
    for (int i = 0; i < len; i++) {
        if (isdigit(equation[i]) == 0 && equation[i] != ' ') {
            pushStackChar(&op, equation[i]);
        }
    }
    return op;
}

int calculate(char* equation, int len) {
    StackChar *operators = newStackChar();
    StackChar *tmpOperators = newStackChar();
    StackInt *output = newStackInt();
    StackInt *tmpOutput = newStackInt();

    while (!isStackCharEmpty(operators)) {
        char operator = popStackChar(&operators);
        int operand = popStackInt(&output);
        switch (operator) {
            case '^': {
                int val = pow(operand, popStackInt(&output));
                pushStackInt(&output, val);
                break;
            }

            case '*': {
                int val = operand * popStackInt(&output);
                pushStackInt(&output, val);
                break;
            }
            case '/': {
                int val = operand / popStackInt(&output);
                pushStackInt(&output, val);
                break;
            }
            default: {
                pushStackChar(&operators, operator);
                pushStackInt(&output, operand);

                tmpOperators->pushStackChar(operator);
                tmpOutput->pushStackInt(operand);
                break;
            }
        }
    }

    return popStackInt(&output);
}

//int calculate(char* equation, int len) {
//    StackChar *operator = newStackChar();
////    StackChar *output = newStackChar();
//    StackInt *output = newStackInt();
//    int offset = 0;
//    for (int i = 0; i < len - offset; i++) {
//// check for parentheses before doing anything else
////fix method and adjust to stackInt
//        if (equation[i] == '(') {
//            int start = i + 1;
//            int end;
//            while (equation[i] != ')') {
//                i++;
//            }
//            end = i - 1;
//            char subEq[end - start + 1];
//            int index = 0;
//            for (int j = start; j <= end; j++) {
//                subEq[index] = equation[j];
//                index++;
//            }
//            pushStackInt(&output, (char) (calculate(subEq, sizeof(subEq))));
//        }
//        switch (equation[i]) {
//            case '(': {
//                int start = i + 1;
//                int end;
//                while (equation[i] != ')') {
//                    i++;
//                }
//                end = i - 1;
//                char subEq[end - start + 1];
//                int index = 0;
//                for (int j = start; j <= end; j++) {
//                    subEq[index] = equation[j];
//                    index++;
//                }
//                pushStackInt(&output, (char) (calculate(subEq, sizeof(subEq))));
//                break;
//            }
//
//            case '*': {
//                if (equation[i+1] == '*') {
//                    i += 3;
//                    int val = pow(popStackChar(&output) - '0', equation[i] - '0');
//                    pushStackChar(&output, (char) (val + '0'));
//                } else {
//                    i += 2;
//                    int val = (popStackChar(&output) - '0') * (equation[i] - '0');
//                    pushStackChar(&output, (char) (val + '0'));
//                }
//                break;
//            }
//            case '/': {
//                i += 2;
//                int val = (popStackChar(&output) - '0') / (equation[i] - '0');
//                int value = (popStackInt(&output) / equation[i] - '0');
//                pushStackInt(&output, value);
//                pushStackChar(&output, (char) (val + '0'));
//                break;
//            }
//            case '+': {
//                pushStackChar(&operator, equation[i]);
//                break;
//            }
//            case '-': {
//                pushStackChar(&operator, equation[i]);
//                break;
//            }
//            default: {
//                int num = 0;
//                if (equation[i] != ' ') {
//                    while (equation[i] != ' ') {
//                        num *= 10;
//                        num += equation[i] - '0';
//                        i++;
//                    }
//                }
//                char val = equation[i];
//                pushStackInt(&output, num);
//                pushStackChar(&output, val);
//                break;
//            }
//        }
//    }
//
//    while (!isStackCharEmpty(operator)) {
//        char op = popStackChar(&operator);
//        if (op == '+') {
//            int val = popStackChar(&output) + popStackChar(&output) - '0';
//            pushStackChar(&output, (char) val);
//        } else if (op == '-') {
//            int val = -popStackChar(&output) + popStackChar(&output) + '0';
//            pushStackChar(&output, (char) val);
//        }
//    }
//
//    return popStackChar(&output) - '0';
//}

int main() {
    char* equation = "31 + 2 + 42 - 8";
    int len = strlen(equation);

    char *ptr = equation;
//    printf("%d", calculate(equation, len));
    StackInt* stack = stringToStack(equation, len);
    StackChar* sc = stringToOp(equation, len);
    while (!isStackCharEmpty(sc)) {
        printf("%c \n", popStackChar(&sc));
    }

    while (!isStackIntEmpty(stack)) {
        printf("%d \n", popStackInt(&stack));
    }
}