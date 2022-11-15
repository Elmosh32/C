#ifndef __BRACKETS_H__
#define __BRACKETS_H__

/**
   Description- Given strings, the function determines whether each sequence of brackets is balanced.
   Auxiliary functions: sameTypeOfBrackets, openBracket, closeBracket.
   1- the function checks if current char is a starting bracket (auxiliary function - openBracket).
    1.1- if TRUE  => The function pushes the bracket to the stack.
    1.2- if FALSE => The function checks if the current char is a closing bracket (auxiliary function - closeBracket).
     1.2.1- if TRUE  => The function checks if the stack is empty.
           1.2.1.1- if TRUE => returns FALSE(unbalanced brackets)
     1.2.2- if FALSE  => The function checks if the substring with the current closing bracket is unbalanced (auxiliary function - balancedBrackets).
           1.2.1.1- if TRUE => returns FALSE(unbalanced brackets)
   2- The function checks if the stack is not empty.
    2.1- if TRUE => returns FALSE(unbalanced brackets)
    2.2- if FALSE => returns TRUE(The expression is balanced.)
   Input-   char word[]
   Output-  If a string is balanced, the function returns TRUE Otherwise, the function returns FALSE.
   Error-   X
 **/
int balancedBrackets(char word[]);

/**
   Description- The function checks if the substring with the current closing bracket (char stringChar) is unbalanced.
   Input-   Stack* _stack,
            char stringChar.
   Output-  TRUE OR FALSE.
   Error-   X
 **/
int sameTypeOfBrackets(Stack* _stack, char stringChar);

/**
   Description- The function checks if the given char is a starting bracket ( ( or {  or [ ) .
   Input-   char ch
   Output-  TRUE OR FALSE.
   Error-   X
 **/
int openBracket(char ch);

/**
   Description- The function checks if the given char is a closing bracket ( ) or  }  or ] ).
   Input-   char ch
   Output-  TRUE OR FALSE.
   Error-   X
 **/
int closeBracket(char ch);

#endif /* __BRACKETS_H__ */
