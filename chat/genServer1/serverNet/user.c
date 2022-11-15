#include "../../../advc/genDoubleList/genDoubleList.h"
#include "../../../advc/genDoubleList/list_itr.h"
#include "../../../advc/genDoubleList/list_functions.h"
#include "user.h"
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 24
#define PASS_LEN 8

struct User
{
    List *m_groups;
    char m_userName[NAME_LEN];
    char m_password[PASS_LEN];
    int m_activeFlag;
    int m_socket;
};

User *CreateUser(char *_userName, char *_password)
{
    User *user;

    if (_userName == NULL || _password == NULL)
    {
        return NULL;
    }

    if ((user = (User *)malloc(sizeof(User))) == NULL)
    {
        return NULL;
    }

    strcpy(user->m_userName, _userName);
    strcpy(user->m_password, _password);
    user->m_activeFlag = 0;
    user->m_socket = -1;

    return user;
}

void DestroyUser(User **_user)
{
    if (_user == NULL || *_user == NULL)
    {
        return;
    }

    ListDestroy(&(*_user)->m_groups, NULL);

    free(*_user);
    *_user = NULL;
}

char *GetUserPassword(User *_user)
{
    if (_user == NULL || _user->m_password == NULL)
    {
        return NULL;
    }
    return _user->m_password;
}

char *GetUserName(User *_user)
{
    if (_user == NULL || _user->m_password == NULL)
    {
        return NULL;
    }
    return _user->m_userName;
}
/* void AddGroupToList(User *_user, Group *_group){}
 void RemoveGroupFromList(User *_user, int *_group){} */
