#include "status.h"
#include "diary.h"

int main(){
        diary* ad = NULL;
        meet* meetingVal = NULL;
        int userChoice = -1, showList = 1, flagInsert = 1, flagAdExist = 0;

        while (userChoice!=10) {
                if(showList == 1) {
                        printf("\nplease insert val from the list:\n");
                        printOptionsList();
                        showList=0;
                }else{
                        printf("\nplease insert val from the list (press 0 to see the list again)\n");
                }

                scanf("%d", &userChoice);

                switch (userChoice) {
                case 0:
                        printOptionsList();
                case 1:
                        if (flagAdExist == 0) {
                                ad = createAD(2,4);
                                flagAdExist = 1;
                        }else{
                                printf("appointment diary already exist\n");
                        }
                        break;
                case 2:
                        if (flagInsert == 1) {
                                printf("%d\n", flagInsert);
                                meetingVal = passElemToCreateMeet(ad, meetingVal);
                                flagInsert = 0;
                        }else{
                                printf("Before create another meeting please insert the existing meeting\n");
                        }
                        break;
                case 3:
                        if (insertApToAD(ad,meetingVal) == 0) {
                                meetingVal = NULL;
                        }
                        flagInsert = 1;
                        break;
                case 4:
                        removeApFromAD(ad);
                        break;
                case 5:
                        findMeeting(ad);
                        break;
                case 6:
                        DestroyAD(ad);
                        break;
                case 7:
                        printMeetings(ad);
                        break;
                case 8:
                        save(ad);
                        break;
                case 9:
                        if(flagAdExist == 1) {
                                load(ad);
                        }else{
                                printf("no ad created\n");
                        }
                        break;
                case 10:
                        break;
                default:
                        printf("\nInvalid choice! Please try again.\n");
                        printOptionsList();
                        break;
                }
        }

        return 0;
}
