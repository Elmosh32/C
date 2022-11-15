
meet * createMeeting(diary* _diary, float _startTime, float _endTime, int _roomNumber);
status removeAllApFromAD(diary* _diary);
status increase(diary* _diary);
status isLegalTime(float _startTime, float _endTime);
status isOverlapping(diary* _diary, float _startTime, float _endTime, int _roomNumber);
status meetingExist(diary* _diary, meet* _meet);
int SearchMeet(diary* _diary, float _start);
void printOptionsList();
void sortMeetings(diary* _diary);
void swap(diary* _diary, int _index1, int _index2);
void shiftRight(diary* _diary, int _index1);
