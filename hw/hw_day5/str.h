/************************************************************************************************
   imports and constant
************************************************************************************************/
#include <stdio.h>
#include <string.h>
#define NULL_ERROR -9

/************************************************************************************************
   main: squeeze   auxiliary-functions: nullCheck
************************************************************************************************/
int squeeze(char *_str1, char *_str2);
/**
   Description- The function squeeze(s1,s2) deletes each character in string s1 that matches
   any character in the string s2.
   the function calling to the auxiliary function nullCheck,
   if nullCheck returns 1 the function returns the NULL_ERROR constant.
   The function calls the sameChar function,
   if sameChar returns 0 The function calls the deleteChar function.
   Input-   char *_str1
            char *_str2
   Output-  integer number- 0 or (NULL_ERROR) -9
   Error-   NULL_ERROR:-9
 **/

/************************************************************************************************
   main: location   auxiliary-function: nullCheck
************************************************************************************************/

int location(char *_str1, char *_str2);
/**
   Description: the function Location (s1,s2) returns the location of string s2 in the s1
   if s1 doesn't contain s2 then return -1,
   if the length of _str1 smaller from the length of _str2 returns -1.
   the function calling to the auxiliary function nullCheck,
   if nullCheck returns 1 the function returns the NULL_ERROR constant.
   Input-   char *_str1
            char *_str2
   Output: -1, -2, -9(NULL_ERROR), positive int (location of string s2 in the s1).
   Error:  -9
 **/

/************************************************************************************************
   main: sTrim   auxiliary-functions: nullCheck
************************************************************************************************/

int sTrim(char _str[]);
/**
   Description- The function gets a string and replaces multiple spaces with a single space.
                the function calling to the auxiliary function nullCheck,
                if nullCheck returns 1 the function returns the NULL_ERROR constant.
                the function calls to charCount to and deleteChar.
                deleteChar deletes all the extra spaces in the string,
                finally the function inserts a NULL value into _str[charCount] and returns 0.
   Input-       char _str[]
   Output-      0 or -9
   Error-       -9(NULL_ERROR)
 **/

/************************************************************************************************
   auxiliary-functions
************************************************************************************************/
int nullCheck(char *_str);
/**
   Description- The function gets a string _str and returns 0 if the string is null otherwise 1
   Input-       char *_str
   Output-      0, 1
   Error-       X
 **/
