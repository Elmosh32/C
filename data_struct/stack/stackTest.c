#include <stdio.h>
#include <stddef.h>

#include "ADTDefs.h"
#include "stack.h"

void crateTest(){
  printf("crateTest\n");

  if(StackCreate(12,1) != NULL)
    printf("StackCreate(12,1) => Passed\n");
  else
    printf("StackCreate(12,1) => Failed\n");

    if(StackCreate(12,0) != NULL)
      printf("StackCreate(12,0) => Passed\n");
    else
      printf("StackCreate(12,0) => Failed\n");

    if(StackCreate(0,1) != NULL)
      printf("StackCreate(0,1) => Passed\n");
    else
      printf("StackCreate(0,1) => Failed\n");

    if(StackCreate(0,0) == NULL)
      printf("StackCreate(0,0) => Passed\n");
    else
      printf("StackCreate(0,0) => Failed\n");

      if(StackCreate(-33,0) != NULL)
        printf("StackCreate(0,0) => Passed\n");
      else
        printf("StackCreate(0,0) => Failed\n");
}
