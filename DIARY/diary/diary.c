#include "diary.h"

diary * createAD(int _size, int _blockSize){
        diary* ad;
        meet** dArrMeeting;

        if(_size <= 0 && _blockSize <= 0)
                return POINTER_NOT_INITIALIZE;
        if((ad = (diary*) malloc (sizeof(diary))) == NULL)
                return POINTER_NOT_INITIALIZE;
        if((dArrMeeting = (meet**)malloc(_size * sizeof(meet*))) == NULL) {
                free(ad);
                return POINTER_NOT_INITIALIZE;
        }

        ad->meeting = dArrMeeting;
        ad->meetingSize = _size;
        ad->meetingBlockSize = _blockSize;
        ad->NumOfMeetings = 0;
        ad->magicNum = MAGIC_NUMBER;

        return ad;
}

meet * createMeeting(diary* _diary, float _startTime, float _endTime, int _roomNumber){
        meet* cMeet;

        if(isLegalTime(_startTime,_endTime) == 0)
                return NULL;

        if(isOverlapping(_diary,_startTime,_endTime,_roomNumber) == 1) {
                printf("overlapping\n");
                return NULL;
        }


        if((cMeet = (meet*) malloc (sizeof(meet))) == NULL)
                return POINTER_NOT_INITIALIZE;

        cMeet->startTime = _startTime;
        cMeet->endTime = _endTime;
        cMeet->room = _roomNumber;

        return cMeet;
}

int isLegalTime(float _startTime, float _endTime){
        if(_endTime >= 24 || _startTime < 0 || _startTime >= _endTime) {
                printf("invalid meeting time\n");
                return 0;
        }
        return 1;
}

int isOverlapping(diary* _diary, float _startTime, float _endTime, int _roomNumber){
        int i, room;
        float start,end;

        for (i = 0; i < _diary->NumOfMeetings; i++) {
                start = _diary->meeting[i]->startTime;
                end = _diary->meeting[i]->endTime;
                room = _diary->meeting[i]->room;
                if(room == _roomNumber && ((start<=_startTime && end>=_startTime) || (start<=_endTime && end>=_endTime)))
                        return 1;
        }
        return 0;
}

int insertApToAD(diary* _diary, meet* _meet){
        int result;
        if(_diary == NULL || _meet == NULL)
                return OVERFLOW;
        if (_diary->magicNum == 0) {
                return EMPTY_AD;
        }
        if (meetingExist(_diary,_meet) == 1) {
                printf("the meeting already exist\n");
                return -1;
        }

        if(_diary->meetingSize == _diary->NumOfMeetings) {
                if((result = increase(_diary)) != OK) {
                        return result;
                }
        }

        _diary->meeting[_diary->NumOfMeetings] = _meet;
        _diary->NumOfMeetings++;
        sortMeetings(_diary);

        return OK;
}

int meetingExist(diary* _diary, meet* _meet){
        int counter = 0;
        meet** dArrMeeting;
        dArrMeeting = _diary->meeting;

        while(counter < _diary->NumOfMeetings) {
                if(*(dArrMeeting+counter) == _meet)
                        return 1;
                counter++;
        }
        return 0;
}

int increase(diary* _diary){
        int newSize;
        meet **me;

        if (_diary->meetingBlockSize == 0) {
                return OVERFLOW;
        }

        newSize = (_diary->meetingSize) + (_diary->meetingBlockSize);
        if((me = (meet**)realloc(_diary->meeting,newSize*sizeof(_diary->meeting)))== NULL) {
                return REALLOC_FAIL;
        }

        _diary->meeting = me;
        _diary->meetingSize = newSize;

        return OK;
}

void sortMeetings(diary* _diary){
        int i, j;

        for (i = 0; i < _diary->NumOfMeetings; ++i)
        {
                for (j = i + 1; j < _diary->NumOfMeetings; ++j)
                {
                        if (_diary->meeting[i]->startTime > _diary->meeting[j]->startTime)
                        {
                                swap(_diary, i, j);
                        }
                }
        }
}

void swap(diary* _diary, int _index1, int _index2){
        float sTimeCpy,eTimeCpy;
        int rNumCpy;

        sTimeCpy = _diary->meeting[_index1]->startTime;
        eTimeCpy = _diary->meeting[_index1]->endTime;
        rNumCpy = _diary->meeting[_index1]->room;

        _diary->meeting[_index1]->startTime = _diary->meeting[_index2]->startTime;
        _diary->meeting[_index1]->endTime = _diary->meeting[_index2]->endTime;
        _diary->meeting[_index1]->room = _diary->meeting[_index2]->room;

        _diary->meeting[_index2]->startTime = sTimeCpy;
        _diary->meeting[_index2]->endTime = eTimeCpy;
        _diary->meeting[_index2]->room = rNumCpy;
}

void printMeetings(diary* _diary){
        int i, room;
        float start,end;
        if (_diary->magicNum == 0) {
                printf("nothing to print!\nto print crate ad and meetings and insert the meetings to your ad.\n");
        }else if(_diary->NumOfMeetings == 0) {
                printf("nothing to print!\nto print insert meetings into ad.\n");
        }else{
                for (i = 0; i < _diary->NumOfMeetings; i++) {
                        start = _diary->meeting[i]->startTime;
                        end = _diary->meeting[i]->endTime;
                        room = _diary->meeting[i]->room;
                        printf("%f\t%f\t%d\n", start, end, room);
                }
        }
}

int removeApFromAD(diary* _diary){
        int i;
        float beginTime;
        printf("Please insert the meeting begin time\n");
        scanf("%f", &beginTime);

        for (i = 0; i < _diary->NumOfMeetings; ++i) {
                if (_diary->meeting[i]->startTime == beginTime) {
                        printf("the meeting in room number %d from %.2f to %.2f was deleted sucssufuly\n", _diary->meeting[i]->room, beginTime, _diary->meeting[i]->endTime);
                        free(_diary->meeting[i]);
                        shiftRight(_diary,i);
                        _diary->NumOfMeetings--;
                        return OK;
                }
        }
        printf("sorry but we dont have any meeting that start at:%f\n", beginTime);
        return OK;
}

void shiftRight(diary* _diary, int _index){
        int i;
        for (i = _index; i < _diary->NumOfMeetings; ++i) {
                _diary->meeting[i] = _diary->meeting[i+1];
        }
}

void DestroyAD(diary* _diary){
        int i;
        if(_diary != NULL) {
                for (i = 0; i < _diary->NumOfMeetings; i++) {
                        free(_diary->meeting[i]);
                }
                free(_diary->meeting);
                free(_diary);
                _diary->magicNum = 0;
        }
}
int findMeeting(diary* _diary){
        int meetIndex, room;
        float start, end, beginTime;
        printf("Please insert the meeting begin time\n");
        scanf("%f", &beginTime);

        meetIndex = SearchMeet(_diary, beginTime);
        if(meetIndex != -1) {
                start = _diary->meeting[meetIndex]->startTime;
                end = _diary->meeting[meetIndex]->endTime;
                room = _diary->meeting[meetIndex]->room;
                printf("%f\t%f\t%d\n", start, end, room);
        }else
                printf("sorry but we dont have any meeting that start at:%d\n", beginTime);
}

int SearchMeet(diary* _diary, float _index)
{
        int mid, left = 0, right = _diary->NumOfMeetings-1;
        while (left <= right) {
                mid = left + (right - left) / 2;

                if (_diary->meeting[mid]->startTime == _index)
                        return mid;

                if (_diary->meeting[mid]->startTime < _index)
                        left = mid + 1;
                else
                        right = mid - 1;

        }

        return -1;
}

void printOptionsList(){
        printf(
                "-------------------------------------------------------------------------------------\n"
                "|   1. Create AD                                                                    |\n"
                "|   2. Create meeting                                                               |\n"
                "|   3. Insert appointment into AD insertion in sorted order (by begin hour)         |\n"
                "|   4. Remove appointment from AD (by begin hour 0)                                 |\n"
                "|   5. Find appointment in AD (by begin hour)                                       |\n"
                "|   6. Destroy AD                                                                   |\n"
                "|   7. Print AD                                                                     |\n"
                "|   8. Exit                                                                         |\n"
                "-------------------------------------------------------------------------------------\n");

}
