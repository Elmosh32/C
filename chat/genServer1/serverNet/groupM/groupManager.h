
#ifndef __GROUP_MANAGER_H__
#define __GROUP_MANAGER_H__

typedef struct GroupManager GroupManager;

/* typedef enum GroupRes
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

} GroupRes;
 */
GroupManager *CreateGroupManager();
/*

void DestroyGroupManager(GroupManager **_groupManager);
LeaveGroup => if the lastuser left call to delete group (group.c api func)
JoinGroup => AddUser
CreateGroup
logout => leave All groups
*/
#endif /* __GROUP_MANAGER_H__ */