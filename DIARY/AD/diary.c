#include "status.h"
#include "diary.h"
#include "diaryAuxilliaryFunc.h"

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

meet* passElemToCreateMeet(diary* _diary, meet* _meet){
        int roomNumber;
        float startTime, endTime;
        if(_meet == NULL) {
                printf("Please enter the meeting start time \n");
                scanf("%f", &startTime);
                printf("Please enter the meeting end time \n");
                scanf("%f", &endTime);
                printf("Please enter the meeting room number \n");
                scanf("%d", &roomNumber);
                return createMeeting(_diary, startTime, endTime, roomNumber);
        }else {
                printf("Error! please insert metting before creating another meeting\n");
        }
}

status insertApToAD(diary* _diary, meet* _meet){
        int result;

        if(_diary == NULL || _meet == NULL)
                return OVERFLOW;

        if (_diary->magicNum == 0) {
                return EMPTY_AD;
        }

        if (meetingExist(_diary,_meet) == TRUE) {
                printf("the meeting already exist\n");
                return APPOINTMENT_ALREADY_EXIST;
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

status save(diary* _diary){
        FILE *meetings;
        char fname[128];
        int i, room;
        float start,end;

        if(_diary == NULL) {
                printf("Error! you must create ad before this action\n");
                return APPOINTMENT_DAIRY_IS_NOT_INITIALIZED;
        }
        printf("Please enter the file name to save from.\n");
        scanf("%s", fname);

        if((meetings = fopen(fname, "w")) == NULL) {
                printf("File could not be open\n");
                return FILE_OPEN_FAILED;
        }else{
                fprintf(meetings,"total number of meetings:%d\n\n", _diary->NumOfMeetings);
                fprintf(meetings,"*start******end******room*\n");
                for (i = 0; i < _diary->NumOfMeetings; i++) {
                        start = _diary->meeting[i]->startTime;
                        end = _diary->meeting[i]->endTime;
                        room = _diary->meeting[i]->room;
                        fprintf(meetings,"|%.2f|\t\t|%.2f|\t\t|%d|\n", start, end, room);
                }
                fclose(meetings);
        }
        return OK;
}

status load(diary* _diary){
        FILE *meetings2;
        char fname[128];
        meet* meetingToInsert = NULL;
        int i, room, exit = 0;
        float start,end;

        if (_diary->NumOfMeetings > 0) {
                printf("warning!! all the meetings will delete.\n");
                printf("if you wish to continue enter 0 else enter 1\n");
                scanf("%d", &exit);
        }

        if (exit == TRUE)
                return STOP_APP;

        printf("Please enter the file name to read from.\n");
        scanf("%s", fname);

        if((meetings2 = fopen(fname, "r")) == NULL) {
                printf("File could not be open\n");
                return FILE_OPEN_FAILED;
        }else{
                removeAllApFromAD(_diary);
                fscanf(meetings2,"%f%f%d",&start, &end, &room);
                while (!feof(meetings2)) {
                        if((meetingToInsert =(createMeeting(_diary, start, end, room))) != NULL) {
                                insertApToAD(_diary,meetingToInsert);
                                printf("%.2f\t\t%.2f\t\t%d\n", start, end, room);
                        }
                        fscanf(meetings2,"%f%f%d",&start, &end, &room);
                }
                fclose(meetings2);
        }
        return OK;
}

meet * createMeeting(diary* _diary, float _startTime, float _endTime, int _roomNumber){
        meet* cMeet;

        if(isLegalTime(_startTime,_endTime) == TIME_ERROR)
                return NULL;

        if(isOverlapping(_diary,_startTime,_endTime,_roomNumber) != OK) {
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

status isLegalTime(float _startTime, float _endTime){
        if(_endTime >= 24 || _startTime < 0 || _startTime >= _endTime) {
                printf("invalid meeting time\n");
                return TIME_ERROR;
        }
        return OK;
}

status isOverlapping(diary* _diary, float _startTime, float _endTime, int _roomNumber){
        int i, room;
        float start,end;

        for (i = 0; i < _diary->NumOfMeetings; i++) {
                start = _diary->meeting[i]->startTime;
                end = _diary->meeting[i]->endTime;
                room = _diary->meeting[i]->room;
                if(room == _roomNumber && ((start<=_startTime && end>=_startTime) || (start<=_endTime && end>=_endTime)))
                        return OVERLAPPING;
        }
        return OK;
}

status meetingExist(diary* _diary, meet* _meet){
        int counter = 0;
        meet** dArrMeeting;
        dArrMeeting = _diary->meeting;

        while(counter < _diary->NumOfMeetings) {
                if(*(dArrMeeting+counter) == _meet)
                        return TRUE;
                counter++;
        }
        return FALSE;
}

status increase(diary* _diary){
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
                        printf("%.2f\t%.2f\t%d\n", start, end, room);
                }
        }
}

status removeApFromAD(diary* _diary){
        int i;
        float beginTime;

        if (_diary == NULL) {
                return APPOINTMENT_DAIRY_IS_NOT_INITIALIZED;
        }

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

status removeAllApFromAD(diary* _diary){
        int i;

        if (_diary == NULL) {
                return APPOINTMENT_DAIRY_IS_NOT_INITIALIZED;
        }

        for (i = 0; i < _diary->NumOfMeetings; ++i) {
                free(_diary->meeting[i]);
        }

        _diary->NumOfMeetings = 0;

        return OK;
}

void shiftRight(diary* _diary, int _index){
        int i;
        for (i = _index; i < _diary->NumOfMeetings; ++i) {
                _diary->meeting[i] = _diary->meeting[i+1];
        }
}

status DestroyAD(diary* _diary){
        int i;
        if(_diary != NULL && _diary->magicNum != 0) {
                for (i = 0; i < _diary->NumOfMeetings; i++) {
                        free(_diary->meeting[i]);
                }
                free(_diary->meeting);
                free(_diary);
                _diary->magicNum = 0;
                return OK;
        }else{
                printf("STRUCT ALREADY DESTROYED\n");
                return STRUCT_ALREADY_DESTROYED;
        }
}

status findMeeting(diary* _diary){
        int meetIndex, room;
        float start, end, beginTime;

        if (_diary == NULL) {
                return APPOINTMENT_DAIRY_IS_NOT_INITIALIZED;
        }

        printf("Please insert the meeting begin time\n");
        scanf("%f", &beginTime);

        meetIndex = SearchMeet(_diary, beginTime);
        if(meetIndex != -1) {
                start = _diary->meeting[meetIndex]->startTime;
                end = _diary->meeting[meetIndex]->endTime;
                room = _diary->meeting[meetIndex]->room;
                printf("%f\t%f\t%d\n", start, end, room);
        }else{
                printf("sorry but we dont have any meeting that start at:%f\n", beginTime);
                return APPOINTMENT_NOT_FOUND;
        }

        return OK;
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

        return APPOINTMENT_NOT_FOUND;
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
                "|   8. Save to file                                                                 |\n"
                "|   9. Read from file                                                               |\n"
                "|  10. Exit                                                                         |\n"
                "-------------------------------------------------------------------------------------\n");
}
