#include <string.h>

#include "ADTDefs.h"
#include "stack.h"
#include "brackets.h"

#define FALSE 0  /* boolean flag */
#define TRUE 1   /* boolean flag */

int balancedBrackets(char word[]){
        struct Stack *st;
        int i, stLen;

        stLen= strlen(word);
        st=StackCreate(stLen,2);

        for (i = 0; i < stLen; i++) {
                if(openBracket(word[i]) != FALSE) {
                        StackPush(st,word[i]);
                }else{
                        if(closeBracket(word[i])) {
                                if(StackIsEmpty(st) == TRUE) {
                                        return FALSE;
                                }else{
                                        if(!(sameTypeOfBrackets(st, word[i]))) {
                                                return FALSE;
                                        }
                                }
                        }
                }
        }

        if(StackIsEmpty(st) == FALSE)
                return FALSE;
        else
                return TRUE;
}

int sameTypeOfBrackets(Stack* _stack, char stringChar){
        int item, item2;

        if(stringChar == ')') {
                StackTop(_stack,&item2);
                StackPop(_stack,&item);
                if(item2 != '(') {
                        return FALSE;
                }
        }

        if(stringChar == ']') {
                StackTop(_stack,&item2);
                StackPop(_stack,&item);
                if(item2 != '[') {
                        return FALSE;
                }
        }

        if(stringChar == '}') {
                StackTop(_stack,&item2);
                StackPop(_stack,&item);
                if(item2 != '{') {
                        return FALSE;
                }
        }

        return TRUE;
}

int openBracket(char ch){
        if(ch == '(' || ch == '{' || ch == '[') {
                return TRUE;
        }
        return FALSE;
}

int closeBracket(char ch){
        if(ch == ')' || ch == '}' || ch == ']') {
                return TRUE;
        }
        return FALSE;
}
