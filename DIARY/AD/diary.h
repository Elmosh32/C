#ifndef __APPOINTMENT_DIARY_H__
#define __APPOINTMENT_DIARY_H__

#include <stdio.h>
#include <stdlib.h>

#define POINTER_NOT_INITIALIZE  NULL
#define MAGIC_NUMBER 9191919
#define TRUE 1
#define FALSE 0

typedef struct appointmentDiary diary;
typedef struct meeting meet;

struct  appointmentDiary {
        struct meeting **meeting;
        int meetingSize;
        int meetingBlockSize;
        int NumOfMeetings;
        int magicNum;
};

struct  meeting {
        int room;
        float startTime;
        float endTime;
};

diary * createAD(int _size, int _blockSize);
meet* passElemToCreateMeet(diary* _diary, meet* _meet);
status insertApToAD(diary * _diary, meet* _meet);
void printMeetings(diary* _diary);
status DestroyAD(diary* _diary);
status findMeeting(diary* _diary);
status removeApFromAD(diary* _diary);
status save(diary* _diary);
status load(diary* _diary);


#endif /* __APPOINTMENT_DIARY_H__ */
