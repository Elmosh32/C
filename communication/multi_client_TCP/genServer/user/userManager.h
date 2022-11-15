#ifndef __USER_MANAGER_H__
#define __USER_MANAGER_H__

#include "../../../../advc/hash/hashMap/genHashMap.h"

typedef enum UserRes
{
    SUCCESS,
} UserRes;

typedef struct UserManager UserManager;

UserManager *CreateUserManager();
int RemoveUser(char *_keyUserName, HashMap *_users);
char *GetName();
char *GetPassword(char *_keyUserName, HashMap *_users);
int GetActiveFlag(char *_keyUserName, HashMap *_users);
int *AddToUsersMap(char *_keyUserName, char *_password, UserManager *_manager);

#endif /* __USER_MANAGER_H__ */