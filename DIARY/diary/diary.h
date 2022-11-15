#include <stdio.h>
#include <stdlib.h>

#define POINTER_NOT_INITIALIZE NULL
#define OK 0
#define OVERFLOW -2
#define REALLOC_FAIL -3
#define UNDERFLOW -4
#define EMPTY_AD -5
#define MAGIC_NUMBER 9191919

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
meet * createMeeting(diary* _diary, float _startTime, float _endTime, int _roomNumber);
int insertApToAD(diary * _diary, meet* _meet);
void sortMeetings(diary* _diary);
void printMeetings(diary* _diary);
void printOptionsList();
void DestroyAD(diary* _diary);
int findMeeting(diary* _diary);
int removeApFromAD(diary* _diary);
void swap(diary* _diary, int _index1, int _index2);
void shiftRight(diary* _diary, int _index1);
int isOverlapping(diary* _diary, float _startTime, float _endTime, int _roomNumber);
int meetingExist(diary* _diary, meet* _meet);
int SearchMeet(diary* _diary, float _start);
int isLegalTime(float _startTime, float _endTime);
