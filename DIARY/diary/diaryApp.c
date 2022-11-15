#include "diary.h"

void Star(int _n)
{
        if (_n == 0)
        {
                printf("sasa\n");
                return;
        }

        Star(_n-1);
        printf("dd\n");

        printf("*\n");

}

int main(){
        Star(4);
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
              printMeetings(ad);
              findMeeting(ad);


              /**
                 removeApFromAD(ad);

                 printOptionsList();

                 removeApFromAD(ad);
                 findMeeting(ad);
                 printMeetings(ad);
                 printf("\nplease insert val from the list:\n");
                 printOptionsList();

                 while (userChoice!=8) {

                      scanf("%d", &userChoice);

                      switch (userChoice) {
                      case 0:
                              printOptionsList();
                      case 1:
                              ad = createAD(2,4);
                              break;
                      case 2:
                              if(meetingVal == NULL) {
                                      printf("Please enter the meeting start time \n");
                                      scanf("%d", &startTime);
                                      printf("Please enter the meeting end time \n");
                                      scanf("%d", &endTime);
                                      printf("Please enter the meeting room number \n");
                                      scanf("%d", &roomNumber);
                                      meetingVal=createMeeting(startTime,endTime,roomNumber);
                              }else {
                                      printf("Error! please insert metting before creating another meeting\n");
                              }
                              break;
                      case 3:
                              if (insertApToAD(ad,meetingVal) == 0) {
                                      meetingVal = NULL;
                              }
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

                      }
                      printf("\nplease insert val from the list (press 0 to see the list again)\n");

                 }
         **/
        return 0;
}
