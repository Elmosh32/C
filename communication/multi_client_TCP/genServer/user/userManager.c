#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include "userManager.h"
#include "../../../../advc/genDoubleList/genDoubleList.h"
#include "../../../../advc/genDoubleList/list_itr.h"
#include "../../../../advc/genDoubleList/list_functions.h"

#define NAME_LEN 24
#define PASS_LEN 8
#define HASH_SIZE 255

typedef struct User User;

struct UserManager
{
    HashMap *m_users;
};

static size_t UserHashFunc(const void *_userName);
static int UserEqualFunc(void *_userName1, void *_userName2);
static void UserToDestroy(void *_User);
static void InitHashFromFile(HashMap *_users);
static void InsertClientToHash(HashMap *_users, FILE *_regUsers);

UserManager *CreateUserManager()
{
    UserManager *user;

    if ((user = (UserManager *)malloc(sizeof(UserManager))) == NULL)
    {
        return NULL;
    }

    user->m_users = HashMap_Create(HASH_SIZE, UserHashFunc, UserEqualFunc);
    if (user->m_users == NULL)
    {
        free(user);
        return NULL;
    }

    InitHashFromFile(user->m_users);

    return user;
}

int *AddToUsersMap(char *_keyUserName, char *_password, UserManager *_manager)
{
    User *user;
    FILE *registeredUsers = fopen("users.txt", "a");

    if (registeredUsers == NULL)
    {
        return -1;
    }

    if (strlen(_keyUserName) < 2 || strlen(_keyUserName) > 24)
    {
        return -1;
    }

    if (strlen(_password) < 2 || strlen(_password) > 8)
    {
        return -1;
    }

    if (GetName(_keyUserName, _manager->m_users) == _keyUserName)
    {
        return -1;
    }

    user = CreateUser(_keyUserName, _password);
    HashMap_Insert(_manager->m_users, _keyUserName, user);
    fprintf(registeredUsers, "%s %s", _keyUserName, _password);
    fclose(registeredUsers);

    return 1;
}

int RemoveUser(char *_keyUserName, HashMap *_users)
{
    void *key = NULL;
    void *value = NULL;

    if (GetName(_keyUserName, _users) == _keyUserName)
    {
        HashMap_Remove(_users, _keyUserName, &key, &value);
        return 1;
    }

    return 0;
}

char *GetName(char *_keyUserName, HashMap *_users)
{
    User *value = NULL;

    if (HashMap_Find(_users, _keyUserName, value) == MAP_SUCCESS)
    {
        return _keyUserName;
    }
    return "The user not found";
}

char *GetPassword(char *_keyUserName, HashMap *_users)
{
    User *value = NULL;
    char *pass;
    if (HashMap_Find(_users, _keyUserName, value) == MAP_SUCCESS)
    {
        strcpy(pass, GetUserPassword(value));
        if (pass == NULL)
        {
            return ("password not found\n");
        }
        return pass;
    }

    return "The user not found";
}

void DestroyUserHash(UserManager *_user)
{
    HashMap_Destroy(&(_user->m_users), NULL, UserToDestroy);
    return;
}

/* user.c */
static void UserToDestroy(void *_User)
{
    free(_User);
    return;
}

static size_t UserHashFunc(const void *_userName)
{
    int sum = 0, i;
    char *userName = (char *)_userName;

    for (i = 0; userName[i] != '\0'; ++i)
    {
        sum += userName[i];
    }

    return sum;
}

static int UserEqualFunc(void *_userName1, void *_userName2)
{
    if (strcmp((char *)_userName1, (char *)_userName2))
    {
        return 1;
    }

    return 0;
}

static void InitHashFromFile(HashMap *_users)
{
    FILE *registeredUsers = fopen("users.txt", "r");
    if (registeredUsers == NULL)
    {
        return;
    }

    while (!feof(registeredUsers))
    {
        InsertClientToHash(_users, registeredUsers);
    }

    InsertClientToHash(_users, registeredUsers);
    fclose(registeredUsers);

    return;
}

static void InsertClientToHash(HashMap *_users, FILE *_regUsers)
{
    User *user;
    char userName[NAME_LEN], password[PASS_LEN];
    int sock;

    fscanf(_regUsers, "%s %s", userName, password);
    user = CreateUser(userName, password);
    HashMap_Insert(_users, userName, user);
}
