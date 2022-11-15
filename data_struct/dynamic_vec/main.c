#include <stdio.h>
#include <stdlib.h>

#include "ADTDefs.h"
#include "vector.h"

int main(){
        struct Vector *vectorCreateT, *VectorDestroyT1, *VectorDestroyT2=NULL, *VectorAddT;
        size_t numOfItems;
        int magicNum;
        int get;

        /** VectorCreate test **/
        /*POSITIVE test*/
        vectorCreateT = VectorCreate(1,2);
        if(vectorCreateT != NULL) {
                printf("|VectorCreate(1,2)|\tVectorCreate POSITIVE test => pass\n");
        }else{
                printf("|VectorCreate(1,2)|\tVectorCreate POSITIVE test => fail\n");
        }

        /*POSITIVE test*/
        vectorCreateT = VectorCreate(2,0);
        if(vectorCreateT != NULL) {
                printf("|VectorCreate(2,0)|\tVectorCreate POSITIVE test => pass\n");
        }else{
                printf("|VectorCreate(2,0)|\tVectorCreate POSITIVE test => fail\n");
        }

        /*POSITIVE test*/
        vectorCreateT = VectorCreate(0,2);
        if(vectorCreateT != NULL) {
                printf("|VectorCreate(0,2)|\tVectorCreate POSITIVE test => pass\n");
        }else{
                printf("|VectorCreate(0,2)|\tVectorCreate POSITIVE test => fail\n");
        }

        /*NEGETIVE test*/
        vectorCreateT = VectorCreate(-2,0);
        if(vectorCreateT == NULL) {
                printf("|VectorCreate(-2,0)|\tVectorCreate NEGETIVE test => pass\n");
        }else{
                printf("|VectorCreate(-2,0)|\tVectorCreate NEGETIVE test => fail\n");
        }

        /*NEGETIVE test*/
        vectorCreateT = VectorCreate(0,0);
        if(vectorCreateT == NULL) {
                printf("|VectorCreate(0,0)|\tVectorCreate NEGETIVE test => pass\n");
        }else{
                printf("|VectorCreate(0,0)|\tVectorCreate NEGETIVE test => fail\n");
        }


        /** VectorDestroy test **/
        VectorDestroyT1 = VectorCreate(2,6);
        VectorDestroy(VectorDestroyT1);
        getMagicNum(VectorDestroyT1,&magicNum);
        if(magicNum == 0) {
                printf("|destroy existing vector once| VectorDestroy POSITIVE test => pass\n");
        }else{
                printf("|destroy existing vector once| VectorDestroy POSITIVE test => fail\n");
        }

        VectorDestroy(VectorDestroyT1);
        getMagicNum(VectorDestroyT1,&magicNum);
        if(magicNum == 0) {
                printf("|destroy existing vector twice| VectorDestroy NEGETIVE test => pass\n");
        }else{
                printf("|destroy existing vector twice| VectorDestroy NEGETIVE test => fail\n");
        }

        VectorDestroy(VectorDestroyT2);
        getMagicNum(VectorDestroyT2,&magicNum);
        if(magicNum != 0) {
                printf("|destroy vector null| VectorDestroy Positive test => pass\n");
        }else{
                printf("|destroy vector null| VectorDestroy Positive test => fail\n");
        }

VectorAddT = VectorCreate(1,6);
	if(VectorAdd(VectorAddT, 4) == 0)
	if(getVector(VectorAddT,0) == 4){
  printf("|destroy vector null| VectorDestroy Positive test => pass\n");
}else{
  printf("|destroy vector null| VectorDestroy Positive test => fail\n");
}

VectorAdd(NULL, 4) == ERR NOT INITIALIZED

/*realloc pass*/
vectorTest = VectorCreate(1,6)
	VectorAdd(vectorTest, 4)
	VectorAdd(vectorTest, 9) == OK
	FUNC(get struct->size == 7 (this is number, not enum)


/*overflow*/
vectorTest = VectorCreate(1,0)
	VectorAdd(vectorTest, 4)
	VectorAdd(vectorTest, 9) == OVERFLOW

/*realloc failed*/
vectorTest = VectorCreate(1,-2)
	VectorAdd(vectorTest, 4) == REALLOCATION FAILED


        /*
           getNumOfItems(vectorCreateT,&numOfItems);
           printf("VectorItemsNum:%ld\n",numOfItems );
           getMagicNum(vectorCreateT,&magicNum);
           printf("%d\n", magicNum);
           VectorDestroyT =VectorCreate(2,6);
           VectorDestroy(VectorDestroyT);
           getMagicNumber == OK
           VectorDestroy(vectorTest)
           getMagicNumber == OK
           VectorDestroy(NULLpointer)
           getMagicNumber != OK

           VectorGet(vectorCreateT,2,&get);
           printf("VectorGet:%d\n",get );

           VectorAdd(vec,10);
           VectorAdd(vec,9);
           VectorAdd(vec,8);
           VectorAdd(vec,7);
           VectorAdd(vec,6);
           VectorAdd(vec,5);
           VectorAdd(vec,4);
           VectorAdd(vec,3);
           VectorAdd(vec,2);
           VectorAdd(vec,1);
           VectorAdd(vec,0);
           VectorItemsNum(vec,&numOfItems);
           VectorGet(vec,2,&get);
           printf("VectorGet:%d\n",get );
           printf("VectorItemsNum:%ld\n",numOfItems );
           VectorDestroy(vec);
           VectorPrint(vec);
           VectorDestroy(vec);
           vec = VectorCreate(11,2);
           VectorPrint(vec);

           VectorAdd(vec,2);
           VectorAdd(vec,1);
           VectorAdd(vec,0);
           VectorPrint(vec);

           printf("\n");
         */
        return 0;
}
