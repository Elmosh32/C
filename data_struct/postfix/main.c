#include <stdio.h>

#include "ex2.h"

int main(){
        char word[]= "((4+8)*(6-5))/((3-2)*(2+2))";
        char *postFix = infixToPostfix(word);
        printf("%s\n",postFix);
        printf("%d\n",postfixCalc(postFix));

        return 0;
}
