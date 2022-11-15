#include <stddef.h>
#include <stdio.h>
int main(){
        FILE *file;
        char fname[128], str[999], c;
        int index;
        printf("Please enter the file name to read from.\n");
        scanf("%s", fname);

        if((file = fopen(fname, "r")) == NULL) {
                printf("File could not be open\n");
                return -1;
        }else{
                index = fseek(file,0,SEEK_END) - 3;
                printf("sasasa\n" );

                while (fgets(str, index, file) ) {
                        printf("%s\n",str);
                }
                fclose(file);
                return 0;
        }
}
