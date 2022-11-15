
#ifndef __GROUP_H__
#define __GROUP_H__

typedef struct Group Group;

typedef enum GroupRes
{
    ADD_SUCCESS,
    ADD_FAIL,
    REMOVE_SUCCESS,
    REMOVE_FAIL,
    NULL_ERR,
    SUCCESS,
    IPSUCESS,
    DUP_USER,
    OK,
    GROUP_REMOVED
} GroupRes;

/**
 * @brief   create a new Group object of given _groupName and _ip
 * @param[in] _groupName
 * @param[in] _ip
 * @return NULL or pointer to Group
 * @retval pointer to Group struct - on success
 * @retval NULL on failure
 */
Group *CreateGroup(char *_groupName, char *_ip);

/**
 * @brief the DestroyUser finction destroys a given Group
 * @param _group - Group to be deallocated.
 * @return  x
 */
void DestroyGroup(Group **_group);

/**
 * @brief  adding user to group
 * @param _group
 * @param _username
 * @return  GroupRes
 * @retval ADD_FAIL
 * @retval DUP_USER
 * @retval ADD_SUCCESS
 */
GroupRes AddUserToGroup(Group *_group, char *_username);

/**
 * @brief  removes user to group
 * @param _group
 * @param _username
 * @return  GroupRes
 * @retval GROUP_REMOVED
 * @retval REMOVE_SUCCESS
 * @retval REMOVE_FAIL
 */
GroupRes RemoveUserFromGroup(Group *_group, char *_username);

/**
 * @brief  getter func - The function copies the group ip to _bufferIP and returns a status
 * @param _group
 * @param _bufferIP
 * @return  GroupRes
 * @retval NULL_ERR
 * @retval SUCCESS
 */
GroupRes GetGroupIp(Group *_group, char *_bufferIP);

/**
 * @brief  getter func - The function copies the group counter to _bufferCounter and returns a status
 * @param _group
 * @param _bufferCounter
 * @return  GroupRes
 * @retval NULL_ERR
 * @retval SUCCESS
 */
GroupRes GetCounter(Group *_group, char *_bufferCounter);

/**
 * @brief  getter func - The function copies the group name to _bufferName and returns a status
 * @param _group
 * @param _bufferName
 * @return  GroupRes
 * @retval NULL_ERR
 * @retval SUCCESS
 */
GroupRes GetName(Group *_group, char *_bufferName);

#endif /* __GROUP_H__ */