#include <stdio.h>

#include "ADTDefs.h"
#include "stack.h"

#define TRUE 1   /* boolean flag */
#define FALSE 0  /* boolean flag */

void nullTest(){
        printf("balanced brackets check - null \n");
        if((balancedBrackets(NULL)) == FALSE) {
                printf("unbalanced => FAIL\n\n");
        }else{
                printf("balanced => PASS\n\n");
        }
}

void emptyStr(){
        printf("balanced brackets check - empty string \n");
        if((balancedBrackets("")) == FALSE) {
                printf("unbalanced => FAIL\n\n");
        }else{
                printf("balanced => PASS\n\n");
        }
}

void withoutBrackets(){
        printf("balanced brackets check - string:\"no brackets\" \n");
        if((balancedBrackets("no brackets")) == 0) {
                printf("unbalanced => FAIL\n\n");
        }else{
                printf("balanced => PASS\n\n");
        }
}

void twoOpenOneClose(){
        printf("balanced brackets check - string:\"((qwe)\" \n");
        if((balancedBrackets("((qwe)")) == FALSE) {
                printf("unbalanced => PASS\n\n");
        }else{
                printf("balanced => FAIL\n\n");
        }
}

void oneOpentwoClose(){
        printf("balanced brackets check - string:\"(qwe))\" \n");
        if((balancedBrackets("(qwe))")) == FALSE) {
                printf("unbalanced => PASS\n\n");
        }else{
                printf("balanced => FAIL\n\n");
        }
}

void firstClose(){
        printf("balanced brackets check - string:\")qwe()\" \n");
        if((balancedBrackets(")qwe()")) == FALSE) {
                printf("unbalanced => PASS\n\n");
        }else{
                printf("balanced => FAIL\n\n");
        }
}

void twoOpenTwoCloseWithOtherChars1(){
        printf("balanced brackets check - string:\"(()qwe)\" \n");
        if((balancedBrackets("(()qwe)")) == FALSE) {
                printf("unbalanced => FAIL\n\n");
        }else{
                printf("balanced => PASS\n\n");
        }
}

void twoOpenTwoCloseWithOtherChars2(){
        printf("balanced brackets check - string:\"(qwe)()\" \n");
        if((balancedBrackets("(qwe)()")) == FALSE) {
                printf("unbalanced => FAIL\n\n");
        }else{
                printf("balanced => PASS\n\n");
        }
}

void twoOpenTwoCloseWithOtherChars3(){
        printf("balanced brackets check - string:\"((qwe))\" \n");
        if((balancedBrackets("((qwe))")) == FALSE) {
                printf("unbalanced => FAIL\n\n");
        }else{
                printf("balanced => PASS\n\n");
        }
}

void twoOpenTwoCloseWithOtherChars4(){
        printf("balanced brackets check - string:\"((some)str)ing\" \n");
        if((balancedBrackets("((some)str)ing")) == FALSE) {
                printf("unbalanced => FAIL\n\n");
        }else{
                printf("balanced => PASS\n\n");
        }
}

void twoOpenTwoCloseWithOtherChars5(){
        printf("balanced brackets check - string:\"(valid))invalid(\" \n");
        if((balancedBrackets("(valid))invalid(")) == FALSE) {
                printf("unbalanced => PASS\n\n");
        }else{
                printf("balanced => FAIL\n\n");
        }
}

void DifferentTypeOfBrackets1(){
        printf("balanced brackets check - string:\"({[]})\" \n");
        if((balancedBrackets("({[]})")) == FALSE) {
                printf("unbalanced => FAIL\n\n");
        }else{
                printf("balanced => PASS\n\n");
        }
}

void DifferentTypeOfBrackets2(){
        printf("balanced brackets check - string:\"({[[]]}[]())\" \n");
        if((balancedBrackets("({[[]]}[]())")) == FALSE) {
                printf("unbalanced => FAIL\n\n");
        }else{
                printf("balanced => PASS\n\n");
        }
}

void DifferentTypeOfBrackets3(){
        printf("balanced brackets check - string:\"some(b{r[a[c]k]e}[t](s)<=>)string\" \n");
        if((balancedBrackets("some(b{r[a[c]k]e}[t](s)<=>)string")) == FALSE) {
                printf("unbalanced => FAIL\n\n");
        }else{
                printf("balanced => PASS\n\n");
        }
}

void DifferentTypeOfBrackets4(){
        printf("balanced brackets check - string:\"(not the same type]\" \n");
        if((balancedBrackets("(invalid]")) == FALSE) {
                printf("unbalanced => PASS\n\n");
        }else{
                printf("balanced => FAIL\n\n");
        }
}

void DifferentTypeOfBrackets5(){
        printf("balanced brackets check - string:\"{[][}]\" \n");
        if((balancedBrackets("{[][}]")) == FALSE) {
                printf("unbalanced => PASS\n\n");
        }else{
                printf("balanced => FAIL\n\n");
        }
}

void moreTests(){
        printf("balanced brackets check - string:\"a+{2*max(A[],5)}>7\" \n");
        if((balancedBrackets("a+{2*max(A[],5)}>7")) == FALSE) {
                printf("unbalanced => FAIL\n\n");
        }else{
                printf("balanced => PASS\n\n");
        }

        printf("balanced brackets check - string:\"a+{2*max(A[],5)}>7)(\" \n");
        if((balancedBrackets("a+{2*max(A[],5)}>7)(")) == FALSE) {
                printf("unbalanced => PASS\n\n");
        }else{
                printf("balanced => FAIL\n\n");
        }

        printf("balanced brackets check - string:\"(a+{2*max(A[],5)}>7)\" \n");
        if((balancedBrackets("(a+{2*max(A[],5)}>7)")) == FALSE) {
                printf("unbalanced => FAIL\n\n");
        }else{
                printf("balanced => PASS\n\n");
        }

        printf("balanced brackets check - string:\")a+{2*max(A[],5)}>7)\" \n");
        if((balancedBrackets(")a+{2*max(A[],5)}>7)")) == FALSE) {
                printf("unbalanced => PASS\n\n");
        }else{
                printf("balanced => FAIL\n\n");
        }
}
