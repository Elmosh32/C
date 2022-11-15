#include <string.h>
#include <stdlib.h>

#include "ADTDefs.h"
#include "stack.h"
#include "ex2.h"

char *infixToPostfix(char word[]){
        struct Stack *st;
        char *newE, ch;
        int i, item2, stLen, counter=0;

        stLen= strlen(word);
        newE= (char*)malloc(sizeof(char)*stLen);
        newE[0]='\0';

        st=StackCreate(stLen,stLen);
        for (i = 0; i < stLen; i++) {
                ch = word[i];
                if(isNumber(ch)) {
                        *(newE+counter)=ch;
                        counter++;
                }else if(word[i] == '(') {
                        StackPush(st,word[i]);
                }else if(word[i] == ')') {
                        if(!StackIsEmpty(st)) {
                                StackTop(st,&item2);
                                while(!StackIsEmpty(st) && item2 != '(' ) {
                                        StackTop(st,&item2);
                                        *(newE+counter)=item2;
                                        counter++;
                                        StackPop(st,&item2);
                                }
                                StackPop(st,&item2);
                        }
                }else if(isOperator(word[i]) && !StackIsEmpty(st)) {
                        StackTop(st,&item2);
                        while(operatorOrder(item2) >= operatorOrder(word[i])) {
                                StackTop(st,&item2);
                                *(newE+counter)=item2;
                                counter++;
                                StackPop(st,&item2);
                        }
                        StackPush(st,word[i]);
                }else if(isOperator(word[i]) && StackIsEmpty(st))
                        StackPush(st,word[i]);
        }

        while(!StackIsEmpty(st)) {
                StackTop(st,&item2);
                *(newE+counter)=item2;
                counter++;
                StackPop(st,&item2);
        }
        return newE;
}


int isNumber(char ch)
{
        return (ch >= '0' && ch <= '9');
}

int isOperator(char ch)
{
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int operatorOrder(char ch)
{
        if(ch == '(')
                return 0;
        if(ch == '+' || ch == '-')
                return 1;
        if(ch == '*' || ch == '/')
                return 2;
        return 0;
}

int postfixCalc(char *s){
        struct Stack *st;
        int left, right, counter=0, item,item2, val;
        st=StackCreate(10,10);

        while(*s != '\0') {
                if(!isOperator(*s)) {
                        val = *s -48;
                        StackPush(st, val);
                }else{
                        StackTop(st, &item);
                        right = item;
                        StackPop(st, &item);
                        StackTop(st, &item);
                        left = item;
                        StackPop(st, &item);

                        if(*s == '+')
                                val = right+left;
                        else if(*s == '-')
                                val = left-right;
                        else if(*s == '*')
                                val = right*left;
                        else if(*s == '/')
                                val = left/right;
                        StackPush(st, val);
                }
                s++;
        }
        StackTop(st, &item);
        return item;
}
