#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include "userManager.h"
#include "../../../advc/hash/hashMap/genHashMap.h"
#include "../../../advc/genDoubleList/genDoubleList.h"
#include "../../../advc/genDoubleList/list_itr.h"
#include "../../../advc/genDoubleList/list_functions.h"

#define NAME_LEN 24
#define PASS_LEN 8
#define HASH_SIZE 255

/* prime numbers for hashFunction */
#define PRIME_NUM_A 3
#define PRIME_NUM_B 7

struct UserManager
{
    HashMap *m_users;
};

static size_t UserHashFunc(const void *_userName);
static int UserEqualFunc(void *_userName1, void *_userName2);
static void UserToDestroy(void *_User);
static void InitHashFromFile(HashMap *_users);
static void InsertClientToHash(HashMap *_users, FILE *_regUsers);

UserManager *UserManagerCreate()
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

int AddToUsersMap(char *_keyUserName, char *_password, UserManager *_manager)
{
    User *user;
    FILE *registeredUsers = fopen("users.txt", "a");
    char str[NAME_LEN];
    if (registeredUsers == NULL)
    {
        return FOPEN_ERROR;
    }

    if (strlen(_keyUserName) < 3 || strlen(_keyUserName) > 24)
    {
        return WRONG_NAME_SIZE;
    }

    if (strlen(_password) < 3 || strlen(_password) > 8)
    {
        return WRONG_PASS_SIZE;
    }

    if (GetName(_keyUserName, _manager->m_users, str) == FOUND)
    {
        return DUPLICATE_USER;
    }

    if ((user = CreateUser(_keyUserName, _password)) == NULL)
    {
        return CREATE_USER_FAIL;
    }

    if ((HashMap_Insert(_manager->m_users, _keyUserName, user)) != MAP_SUCCESS)
    {
        return HASH_INSERT_FAIL;
    }

    fprintf(registeredUsers, "%s %s ", _keyUserName, _password);
    fclose(registeredUsers);

    return USER_SUCCESS;
}

int RemoveUser(char *_keyUserName, UserManager *_manager)
{
    void *key = NULL, *value = NULL;
    char *res;
    char str[NAME_LEN];

    if (_keyUserName == NULL || _manager == NULL)
    {
        return HASH_REMOVE_FAIL;
    }

    if (GetName(_keyUserName, _manager, str) == FOUND)
    {
        if ((HashMap_Remove(_manager->m_users, _keyUserName, &key, &value)) == MAP_SUCCESS)
        {
            return USER_SUCCESS;
        }
        return HASH_REMOVE_FAIL;
    }

    /* USER NOT EXIST ERROR */
    return 0;
}

int GetName(char *_keyUserName, UserManager *_manager, char *_bufferName)
{
    void *value;

    if (_keyUserName == NULL || _manager == NULL)
    {
        return NOT_FOUND;
    }

    if ((HashMap_Find(_manager->m_users, _keyUserName, &value)) == MAP_SUCCESS)
    {
        _bufferName = GetUserName((User *)value);
        return FOUND;
    }

    return NOT_FOUND;
}

int GetPassword(char *_keyUserName, UserManager *_manager, char *_bufferPass)
{
    void *value;
    char *pass;

    if (_keyUserName == NULL || _manager == NULL)
    {
        return NOT_FOUND;
    }

    if (HashMap_Find(_manager->m_users, _keyUserName, &value) == MAP_SUCCESS)
    {
        _bufferPass = GetUserPassword((User *)value);
        if (_bufferPass == NULL)
        {
            return NOT_FOUND;
        }
        return FOUND;
    }

    return NOT_FOUND;
}

void DestroyUserHash(UserManager *_user)
{
    HashMap_Destroy(&(_user->m_users), NULL, UserToDestroy);
    return;
}

static void UserToDestroy(void *_User)
{
    free(_User);
    return;
}

static size_t UserHashFunc(const void *_userName)
{
    int hash, i;
    char *userName = (char *)_userName;

    for (i = 0; userName[i] != '\0'; ++i)
    {
        hash += PRIME_NUM_A + (userName[i] % PRIME_NUM_B);
    }

    return hash;
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

    if (registeredUsers == NULL || _users == NULL)
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
