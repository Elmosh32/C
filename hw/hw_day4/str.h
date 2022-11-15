#define ZERO_ASCI_VAL 48
#define NINE_ASCI_VAL 57
#define NULL_ERROR -1
/**
   Description- The function gets a string and returns the reverse string
   Input-   char *_str
   Output-  char *retVal
   Error- X
 **/
char* reverse(char *_str);

/**
   Description- The function gets a string and checks if it is a palindrome
   Input-   char *_str - string to check
            char *_revStr - the reversed string of _str
   Output-  returns 1 if the string is palindrome and 0 if not
   Error- X
 **/
int isPal(char *_str, char *_revStr);

/**
   Description- atoi function
   Input-   char *_str
   Output-  returns int num(the int value of the number in the _str)
   Error- X
 **/
int myAtoI(char *_str);

/**
   Description- itoa function
   Input-   int _num
            char *_buf
   Output-  returns char *_buf(a string that represents the given number)
   Error- X
 **/
char* myItoA(int _num, char *_buf);

/**
   Description- auxiliary function (returns reversed string to myItoA())
   Input-   char *_buf
            int start
            int end
   Output-  returns void
   Error- X
 **/
void rotate(char *_buf, int start, int end);

int skipBlanks(char *_str);

int checkSign(char * _str, int _i);

int calculateNum(char * _str, int _i, int _sign);
