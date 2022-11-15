#include <stdlib.h>
#include "group.h"
#include "../../../../advc/genDoubleList/genDoubleList.h"
#include "../../../../advc/genDoubleList/list_itr.h"
#include "../../../../advc/genDoubleList/list_functions.h"
#include "../../../../advc/hash/hashMap/genHashMap.h"

#define GROUP_LEN 24

typedef struct Group
{
    char m_groupName[GROUP_LEN];
    List *m_users;
    int m_counter;
    /*
    ip
    port
    */
} Group;

Group *GroupCreate()
{
    Group *group;
    List *userList;

    group = (Group *)malloc(sizeof(Group));
    if (NULL == group)
    {
        return NULL;
    }

    if ((userList = ListCreate()) == NULL)
    {
        return NULL;
    }

    group->m_counter = 0;

    return group;
}