#include <stdio.h>
#include "str.h"

int main()
{
        char str[]= "abbea";
        int i;
        char buf[20];

        printf("original:%s\trev:%s\n",str,reverse(str));
        printf("is pal-%d\n",isPal(str,reverse(str)));
        printf("is atoi: %d\n",myAtoI("-12 4 "));
        printf("str: %s\n",myItoA(-102, buf));
        printf("is atoi: %d\n",myAtoI("-94 4 "));
        printf("is atoi: %d\n",myAtoI("-04 4 "));

        printf("is atoi: %d\n",myAtoI(" -12 4 "));
        printf("is atoi: %d\n",myAtoI("     -94 4 "));
        printf("is atoi: %d\n",myAtoI("              -04    4 "));

        printf("is atoi: %d\n",myAtoI("0 5"));
        printf("is atoi: %d\n",myAtoI("11 5"));
        printf("is atoi: %d\n",myAtoI("531 5"));

        printf("is atoi: %d\n",myAtoI("  0 5"));
        printf("is atoi: %d\n",myAtoI("     11 5"));
        printf("is atoi: %d\n",myAtoI("         531 5"));

        printf("is atoi: %d\n",myAtoI("+11 5"));
        printf("is atoi: %d\n",myAtoI("+2 5"));
        printf("is atoi: %d\n",myAtoI("  +11 5"));
        printf("is atoi: %d\n",myAtoI("+   2 5"));
        printf("is atoi: %d\n",myAtoI("- 8"));
        printf("is atoi: %d\n",myAtoI("-c "));
        printf("is atoi: %d\n",myAtoI("SA 33s"));

        /**

           printf("str: %s\n",myItoA(12345, buf));
           printf("str: %s\n",myItoA(42, buf));
           printf("str: %s\n",myItoA(-12345, buf));
         **/

        return 0;
}
