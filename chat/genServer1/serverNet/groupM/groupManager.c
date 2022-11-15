#include <stdlib.h>
#include "groupManager.h"
#include "../../../advc/genDoubleList/genDoubleList.h"
#include "../../../advc/genDoubleList/list_itr.h"
#include "../../../advc/genDoubleList/list_functions.h"
#include "../../../advc/hash/hashMap/genHashMap.h"

struct GroupManager
{
    HashMap *m_groups;
};

GroupManager *CreateGroupManager()
{
}