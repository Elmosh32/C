#include "str.h"

int main()
{
        char str1[] = "ABBBCBBDBBEFBB", str2[] = "BKE", s[]="             he     was    a good          guy    ";
        char str11[100] = "This is ", str21[] = "myStrcat";
        char str111[20] = "C programming", str211[20];
        char re1[] = "hello world", re2[]="eod";

        printf("S1:%s\n",str111);
        printf("S2:%s\n",str211);
        myStrcpy(str211,str111);
        printf("myStrcpy- S2:%s\n",str211);
        printf("\n");

        printf("source:%s\n",str11);
        printf("dest:%s\n",str21);
        myStrcat(str11,str21);
        printf("myStrcat- source:%s\n",str11);
        printf("\n");

        printf("strcmp(\"avvv\",\"avv\")); => %d\n", strcmp("avvv","avv"));
        printf("myStrcmp(\"avvv\",\"avv\")); => %d\n", myStrcmp("avvv","avv"));
        printf("strcmp(\"av\",\"avv\")); => %d\n", strcmp("av","avv"));
        printf("myStrcmp(\"av\",\"avv\")); => %d\n", myStrcmp("av","avv"));
        printf("strcmp(\"av\",\"av\")); => %d\n", strcmp("av","av"));
        printf("myStrcmp(\"av\",\"av\")); => %d\n", myStrcmp("av","av"));
        printf("\n");

        printf("***squeeze***\n");
        printf("s1:%s\n",str1);
        printf("s2:%s\n",str2);
        squeeze(str1,str2);
        printf("squeeze:%s\n",str1 );
        printf("\n");

        printf("***location***\n");
        printf("s1:%s\n","ABCDEF");
        printf("s2:%s\n","CD");
        printf("location:%d\n",location("ABCDEF","CD"));
        printf("\n");
        printf("s1:%s\n","ABCDEF");
        printf("s2:%s\n","BKE");
        printf("location:%d\n",location("ABCDEF","BKE"));
        printf("\n");

        printf("***sTrim***\n");
        printf("s:%s\n",s);
        sTrim(s);
        printf("sTrim:%s\n",s);
        printf("\n");

        printf("***replace***\n");
        printf("s1:hello world\nsd:eod\n");
        replace(re1,re2);
        printf("replace:%s\n",re1);

        return 0;
}
