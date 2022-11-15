
#ifndef __USER_H__
#define __USER_H__

typedef struct User User;

int *CreateUser(char *_userName, char *_password);
void DestroyUser(User **_user);

char *GetUserPassword(User *_user);

/*
void AddGroupToList(User *_user, Group *_group);
void RemoveGroupFromList(User *_user, int *_group);
*/

#endif /* __USER_H__ */