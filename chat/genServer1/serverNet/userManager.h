#ifndef __USER_MANAGER_H__
#define __USER_MANAGER_H__

typedef enum UserRes
{
    USER_SUCCESS,
    FOPEN_ERROR,
    WRONG_NAME_SIZE,
    WRONG_PASS_SIZE,
    DUPLICATE_USER,
    CREATE_USER_FAIL,
    HASH_INSERT_FAIL,
    HASH_REMOVE_FAIL,
    FOUND,
    NOT_FOUND

} UserRes;

typedef struct UserManager UserManager;

UserManager *UserManagerCreate();
int RemoveUser(char *_keyUserName, UserManager *_manager);
int GetName(char *_keyUserName, UserManager *_manager, char *_bufferName);
int GetPassword(char *_keyUserName, UserManager *_manager, char *_bufferPass);
int AddToUsersMap(char *_keyUserName, char *_password, UserManager *_manager);

#endif /* __USER_MANAGER_H__ */