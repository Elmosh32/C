#include <stdio.h> /* printf */

#include "status.h"
#include "diary.h"
#include "diaryAuxilliaryFunc.h"

/**
        diary* ad;
        meet* meetingVal = NULL;
        int userChoice = -1;

        ad=createAD(2,4);

        meetingVal=createMeeting(ad,1,2,1);
        insertApToAD(ad,meetingVal);
        meetingVal=createMeeting(ad,5,7,1);
        insertApToAD(ad,meetingVal);
        meetingVal=createMeeting(ad,3.5,4.8,1);
        insertApToAD(ad,meetingVal);
        meetingVal=createMeeting(ad,3,6,1);
        insertApToAD(ad,meetingVal);
        meetingVal=createMeeting(ad,0,1,1);
        insertApToAD(ad,meetingVal);
        meetingVal=createMeeting(ad,3,3.1,1);
        insertApToAD(ad,meetingVal);
        insertApToAD(ad,meetingVal);
        insertApToAD(ad,meetingVal);
        meetingVal=createMeeting(ad,12,55.1,1);
        insertApToAD(ad,meetingVal);
        meetingVal=createMeeting(ad,-9,-2,1);
        insertApToAD(ad,meetingVal);
        save(ad);
        printMeetings(ad);

        load(ad);
        printf("\n");
        printMeetings(ad);
           printMeetings(ad);
           findMeeting(ad);

           removeApFromAD(ad);

           printOptionsList();

           removeApFromAD(ad);
           findMeeting(ad);
           printMeetings(ad);
           printf("\nplease insert val from the list:\n");
 **/


void createADT1()
{
        diary* ad;
        ad=createAD(0,0);

        printf("createAD(0,0)\t=>");

        if(ad != NULL) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void createADT2()
{
        diary* ad;
        ad=createAD(0,2);

        printf("createAD(0,2)\t=>");

        if(ad == NULL) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void createADT3()
{
        diary* ad;
        ad=createAD(2,0);

        printf("createAD(2,0)\t=>");

        if(ad == NULL) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void createADT4()
{
        diary* ad;
        ad=createAD(2,3);

        printf("createAD(2,3)\t=>");

        if(ad == NULL) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void createMeetingT1()
{
        diary* ad;
        meet* meetingVal = NULL;

        ad=createAD(2,3);

        meetingVal = createMeeting(ad,-3,2,2);
        printf("createMeeting(ad,-3,2,2)\t=>");

        if(meetingVal != NULL) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void createMeetingT2()
{
        diary* ad;
        meet* meetingVal = NULL;

        ad=createAD(2,3);
        meetingVal = createMeeting(ad,32,2,2);
        printf("createMeeting(ad,32,2,2)\t=>");

        if(meetingVal != NULL) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void createMeetingT3()
{
        diary* ad;
        meet* meetingVal = NULL;

        ad=createAD(2,3);
        meetingVal = createMeeting(ad,2,-2,2);
        printf("createMeeting(ad,2,-2,2)\t=>");

        if(meetingVal != NULL) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void createMeetingT4()
{
        diary* ad;
        meet* meetingVal = NULL;

        ad=createAD(2,3);
        meetingVal = createMeeting(ad,2,42,2);
        printf("createMeeting(ad,2,42,2)\t=>");

        if(meetingVal != NULL) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void createMeetingT5()
{
        diary* ad;
        meet* meetingVal = NULL;

        ad=createAD(2,3);
        meetingVal = createMeeting(ad,2,1,2);
        printf("createMeeting(ad,2,1,22)\t=>");

        if(meetingVal != NULL) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void createMeetingT6()
{
        diary* ad;
        meet* meetingVal = NULL;

        ad=createAD(2,3);
        meetingVal = createMeeting(ad,2,3,2);
        printf("createMeeting(ad,2,3,22)\t=>");

        if(meetingVal == NULL) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void insertApToADT1()
{
        diary* ad = NULL;

        ad=createAD(2,3);

        printf("insertApToAD(ad,NULL)\t=>");

        if(insertApToAD(ad,NULL) == OK) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void insertApToADT2()
{
        diary* ad = NULL;
        meet* meetingVal = NULL;

        ad=createAD(2,3);
        meetingVal = createMeeting(ad,2,1,2);

        printf("insertApToAD(NULL,meet)\t=>");

        if(insertApToAD(NULL,meetingVal) == OK) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void insertApToADT3()
{
        printf("insertApToAD(NULL,NULL)\t=>");

        if(insertApToAD(NULL,NULL) == OK) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void insertApToADT4()
{
        diary* ad;
        meet* meetingVal = NULL;

        ad=createAD(2,3);
        meetingVal = createMeeting(ad,2,1,2);
        DestroyAD(ad);
        printf("insertApToAD after destroy\t=>");

        if(insertApToAD(ad,meetingVal) == OK) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void insertApToADT5()
{
        diary* ad;
        meet* meetingVal = NULL;

        ad=createAD(2,3);
        meetingVal = createMeeting(ad,2,1,2);
        insertApToAD(ad,meetingVal);
        meetingVal = createMeeting(ad,2,1,2);

        printf("insertApToAD insert same meeting twice\t=>");

        if(insertApToAD(ad,meetingVal) == OK) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void insertApToADT6()
{
        diary* ad;
        meet* meetingVal = NULL;

        ad=createAD(4,3);
        meetingVal = createMeeting(ad,2,7,2);

        printf("insertApToAD valid insert\t=>");
        if(insertApToAD(ad,meetingVal) != OK) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void removeApFromADT1()
{


        printf("removeApFromAD(NULL)\t=>");

        if(removeApFromAD(NULL) == OK) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void findMeetingT1()
{
        printf("findMeeting(NULL)\t=>");

        if(findMeeting(NULL) == OK) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void DestroyADT1()
{
        printf("DestroyAD(NULL)\t=>");

        if(DestroyAD(NULL) == OK) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void DestroyADT2()
{
        diary* ad;
        ad=createAD(4,3);
        DestroyAD(ad);
        printf("DestroyAD twice\t=>");

        if(DestroyAD(ad) == OK) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}

void DestroyADT3()
{
        diary* ad;
        ad=createAD(4,3);

        printf("DestroyAD once\t=>");

        if(DestroyAD(ad) != OK) {
                printf("\tFAIL\n");
        }else{
                printf("\tPASS\n");
        }
}
int main(void)
{
        printf("\n******************************************************************************\n"
               "                             createAD tests                                   \n"
               "******************************************************************************\n");
        createADT1();
        createADT2();
        createADT3();

        printf("\n******************************************************************************\n"
               "                          createMeeting tests                                   \n"
               "******************************************************************************\n");
        createMeetingT1();
        createMeetingT2();
        createMeetingT3();
        createMeetingT4();
        createMeetingT5();
        createMeetingT6();

        printf("\n******************************************************************************\n"
               "                          insertApToAD tests                                   \n"
               "******************************************************************************\n");
        insertApToADT1();
        insertApToADT2();
        insertApToADT3();
        insertApToADT4();
        insertApToADT5();
        insertApToADT6();

        printf("\n******************************************************************************\n"
               "                          removeApFromAD tests                                   \n"
               "******************************************************************************\n");
        removeApFromADT1();

        printf("\n******************************************************************************\n"
               "                          findMeeting tests                                   \n"
               "******************************************************************************\n");
        findMeetingT1();

        printf("\n******************************************************************************\n"
               "                          DestroyADT1 tests                                   \n"
               "******************************************************************************\n");
        DestroyADT1();
        DestroyADT2();
        DestroyADT3();
        return 0;
}
